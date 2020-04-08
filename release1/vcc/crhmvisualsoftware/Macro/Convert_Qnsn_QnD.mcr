Convert_Qnsn_QnD
declreadobs, Qnsn, NOBS, description, (W/m^2)
declobs,QnD#, NHRU, description, (W/m^2)
command
if(STEP%FREQ == 1) QnD#[hh] = Qnsn[hh]*0.0864/FREQ else QnD#[hh] = QnD#[hh] + Qnsn[hh]*0.0864/FREQ endif
end
