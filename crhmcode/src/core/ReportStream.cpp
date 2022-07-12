#include "ReportStream.h"

ReportStream::ReportStream(std::string reportName)
{
	this->reportFileStream = new std::basic_ofstream<char, std::char_traits<char>>();
	this->reportFileStream->open(reportName);

	if (!this->reportFileStream->is_open())
	{
		CRHMException e = CRHMException("Cannot open file " + reportName + " to save report.", TExcept::ERR);
		CRHMLogger::instance()->log_run_error(e);
	}
}

void ReportStream::OutputHeaders(CRHMmain * instance)
{
	std::list<std::string>* headerLines = new std::list<std::string>();

	if (instance->OutputFormat == OUTPUT_FORMAT::STD)
	{
		//standard output header
		headerLines = this->RprtHeader(instance);
	}
	else if (instance->OutputFormat == OUTPUT_FORMAT::OBS)
	{
		//.obs file output header
		headerLines = this->RprtHeaderObs(instance);
	}
	else
	{
		CRHMException e = CRHMException("No output format was specified defaulting to STD.", TExcept::WARNING);
		CRHMLogger::instance()->log_run_error(e);
		//standard output header
		headerLines = this->RprtHeader(instance);
	}

	for (
		std::list<std::string>::iterator it = headerLines->begin();
		it != headerLines->end();
		it++
		)
	{
		*(this->reportFileStream)<<(it->c_str());
		*(this->reportFileStream)<<("\n");
	}

	this->reportFileStream->flush();
}


void ReportStream::OutputSummaryHeaders(std::list<std::pair<std::string, TSeries*>>* series)
{
	std::string line;

	line = "time";
	for (
		std::list<std::pair<std::string, TSeries*>>::iterator it = series->begin();
		it != series->end();
		it++
		)
	{
		std::string S = it->second->getTitle();
		line += " " + S;
	}
	*(this->reportFileStream) << (line.c_str());

	*(this->reportFileStream) << '\n';

	line = "units";
	for (
		std::list<std::pair<std::string, TSeries*>>::iterator it = series->begin();
		it != series->end();
		it++
		)
	{
		ClassVar* thisVar = it->second->getTag();
		std::string S = thisVar->units;
		line += " " + S;
	}
	*(this->reportFileStream) << (line.c_str());
	*(this->reportFileStream) << '\n';

	this->reportFileStream->flush();
}


void ReportStream::OutputSummaryLines(std::list<std::pair<std::string, TSeries*>>* series)
{
	TSeries * firstSeries = series->begin()->second;

	for (int i = 0; i < firstSeries->Count(); i++)
	{
		std::string line;

		switch (Global::TimeFormat)
		{
		case TIMEFORMAT::MS:
			line = FloatToStrF(firstSeries->XValue(i), TFloatFormat::ffGeneral, 10, 0);
			break;
		case TIMEFORMAT::YYYYMMDD:
			line = StandardConverterUtility::FormatDateTime("yyyy-mm-dd hh:mm ", firstSeries->XValue(i));
			break;
		case TIMEFORMAT::ISO:
			line = StandardConverterUtility::FormatDateTime("ISO", firstSeries->XValue(i));
			break;
		default:
			break;
		}

		for (
			std::list<std::pair<std::string, TSeries*>>::iterator it = series->begin();
			it != series->end();
			it++
			)
		{
			std::string S = std::to_string(it->second->YValue(i));
			line += " " + S;
		}

		*(this->reportFileStream) << (line.c_str());
		*(this->reportFileStream) << '\n';
	}

	this->reportFileStream->flush();
}


void ReportStream::SendTimeStepToReport(CRHMmain * instance) 
{

	long index = Global::DTindx - Global::DTmin;

	std::string Sx = FloatToStrF(instance->cdSeries[0]->XValue(index), TFloatFormat::ffGeneral, 10, 0);
	Sx = StandardConverterUtility::GetDateTimeInStringForOutput(instance->cdSeries[0]->XValue(index));

	//added this switch statement according to Peter's code.
	switch (Global::TimeFormat) 
	{
	case TIMEFORMAT::MS:
		Sx = FloatToStrF(instance->cdSeries[0]->XValue(index), TFloatFormat::ffGeneral, 10, 0);
		break;
	case TIMEFORMAT::YYYYMMDD:
		Sx = StandardConverterUtility::FormatDateTime("yyyy-mm-dd hh:mm ", instance->cdSeries[0]->XValue(index));
		break;
	case TIMEFORMAT::ISO:
		Sx = StandardConverterUtility::FormatDateTime("ISO", instance->cdSeries[0]->XValue(index));
		break;
	default:
		break;
	}

	for (size_t vv = 0; vv < instance->SelectedVariables->size(); ++vv) 
	{
		// has to equal first series length
		if (instance->cdSeries[0]->Count() == instance->cdSeries[vv]->Count()) 
		{ 
			ClassVar* thisVar = instance->cdSeries[vv]->getTag();
			int prec = 7;
			//Manishankar did this, because GCC is showing segmentation fault here. thisVar remains null.

			if (thisVar->varType == TVar::Int || thisVar->varType == TVar::ReadI)
			{
				prec = 7;
			}

			std::string Sy = FloatToStrF(instance->cdSeries[vv]->YValue(index), TFloatFormat::ffGeneral, prec, 10);
			Sx = Sx + instance->Delimiter + Sy;
		}
	}

	*(this->reportFileStream)<<(Sx);
	*(this->reportFileStream)<<("\n");
}

void ReportStream::CloseStream() 
{
	this->reportFileStream->flush();
	this->reportFileStream->close();
}

std::list<std::string> * ReportStream::RprtHeader(CRHMmain* instance)
{
	std::string Sx;
	std::string Sy;

	std::list<std::string>* headerLines = new std::list<std::string>();

	Sx = "time";
	for (size_t vv = 0; vv < instance->SelectedVariables->size(); ++vv) 
	{
		std::string S = instance->cdSeries[vv]->getTitle();
		Sx += instance->Delimiter + S;
	}
	headerLines->push_back(Sx);

	Sx = "units";
	for (size_t vv = 0; vv < instance->SelectedVariables->size(); ++vv) 
	{
		ClassVar* thisVar = instance->cdSeries[vv]->getTag();
		std::string S = thisVar->units;
		Sx += instance->Delimiter + S;
	}
	headerLines->push_back(Sx);

	return headerLines;
}

std::list<std::string> * ReportStream::RprtHeaderObs(CRHMmain* instance)
{
	std::string Sx;
	std::string Sy;

	std::list<std::string>* headerLines = new std::list<std::string>();

	headerLines->push_back("Future File Description");

	for (size_t vv = 0; vv < instance->SelectedVariables->size(); ++vv) 
	{
		ClassVar* thisVar = instance->cdSeries[vv]->getTag();
		Sx = instance->cdSeries[vv]->getTitle();
		Sx += string(" 1 ");
		Sx += thisVar->units;
		headerLines->push_back(Sx);
	}

	Sx = "###### time";
	for (size_t vv = 0; vv < instance->SelectedVariables->size(); ++vv) 
	{
		std::string S = instance->cdSeries[vv]->getTitle();
		Sx += instance->Delimiter + S;
	}
	
	headerLines->push_back(Sx);

	return headerLines;
}
