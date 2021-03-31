object ShapeForm: TShapeForm
  Left = 409
  Top = 222
  Width = 782
  Height = 540
  Caption = 'Shape'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnActivate = FormActivate
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Chart: TChart
    Left = 137
    Top = 33
    Width = 637
    Height = 453
    Title.Text.Strings = (
      'TChart')
    AxisVisible = False
    Chart3DPercent = 1
    Align = alClient
    TabOrder = 0
    object Series1: TMapSeries
      Marks.Callout.Brush.Color = clBlack
      Marks.BackColor = clSilver
      Marks.Color = clSilver
      Marks.Font.Shadow.Color = 4194368
      Marks.MultiLine = True
      Marks.Style = smsLabelValue
      Marks.Visible = True
      PaletteStep = 50
      PaletteSteps = 10
      Shapes = <
        item
          Color = 16230034
          Text = 'A'
          Z = 0.055
        end
        item
          Color = 16230034
          Text = 'B'
          Z = 0.17
        end
        item
          Color = 16230034
          Text = 'C'
          Z = 0.202
        end
        item
          Color = 16230034
          Text = 'D'
          Z = 0.069
        end
        item
          Color = 16230034
          Text = 'E'
          Z = 0.331
        end
        item
          Color = 16230034
          Text = 'F'
          Z = 0.477
        end
        item
          Color = 16230034
          Text = 'G'
          Z = 0.647
        end
        item
          Color = 16230034
          Text = 'H'
          Z = 0.165
        end
        item
          Color = 16230034
          Text = 'I'
          Z = 0.784
        end
        item
          Color = 16230034
          Text = 'J'
          Z = 0.692
        end
        item
          Color = 16230034
          Text = 'K'
          Z = 0.87
        end
        item
          Color = 16230034
          Text = 'L'
          Z = 0.061
        end>
      UseColorRange = False
      UsePalette = True
      XValues.Name = 'X'
      XValues.Order = loNone
      YValues.Name = 'Y'
      YValues.Order = loNone
      ZValues.Name = 'Z'
      ZValues.Order = loNone
    end
  end
  object TeeCommander1: TTeeCommander
    Left = 0
    Top = 0
    Width = 774
    Height = 33
    Panel = Chart
    Align = alTop
    ParentShowHint = False
    TabOrder = 1
    ChartEditor = ChartEditor1
    Previewer = ChartPreviewer1
  end
  object Panel1: TPanel
    Left = 0
    Top = 33
    Width = 137
    Height = 453
    Align = alLeft
    TabOrder = 2
    object ListBox1: TListBox
      Left = 1
      Top = 1
      Width = 135
      Height = 386
      Align = alClient
      ItemHeight = 13
      TabOrder = 0
      OnClick = ListBox1Click
    end
    object Panel2: TPanel
      Left = 1
      Top = 387
      Width = 135
      Height = 65
      Align = alBottom
      TabOrder = 1
      DesignSize = (
        135
        65)
      object DateTimePicker1: TDateTimePicker
        Left = 0
        Top = 8
        Width = 137
        Height = 25
        Anchors = [akLeft, akTop, akRight, akBottom]
        CalAlignment = dtaLeft
        Date = 0.660297800903209
        Time = 0.660297800903209
        DateFormat = dfShort
        DateMode = dmComboBox
        Kind = dtkDate
        ParseInput = False
        TabOrder = 0
        OnChange = DateTimePicker1Change
      end
      object DateTimePicker2: TDateTimePicker
        Left = 0
        Top = 40
        Width = 137
        Height = 25
        Anchors = [akLeft, akTop, akRight, akBottom]
        BiDiMode = bdLeftToRight
        CalAlignment = dtaRight
        Date = 36929.5
        Time = 36929.5
        DateFormat = dfShort
        DateMode = dmComboBox
        Kind = dtkTime
        ParseInput = False
        ParentBiDiMode = False
        TabOrder = 1
        OnChange = DateTimePicker2Change
      end
    end
  end
  object OpenDialogShape: TOpenDialog
    Left = 136
    Top = 128
  end
  object MainMenu1: TMainMenu
    Left = 208
    Top = 89
    object File1: TMenuItem
      Caption = '&File'
      object Open1: TMenuItem
        Caption = '&Open'
        OnClick = File1Click
      end
      object Grid1: TMenuItem
        Caption = 'Grid'
        OnClick = Grid1Click
      end
    end
    object Display1: TMenuItem
      Caption = '&Display'
      object Variables1: TMenuItem
        Caption = '&Variables'
        Checked = True
        RadioItem = True
        OnClick = Variables1Click
      end
      object Parameters1: TMenuItem
        Caption = '&Parameters'
        RadioItem = True
        OnClick = Parameters1Click
      end
    end
  end
  object ChartPreviewer1: TChartPreviewer
    Chart = Chart
    Left = 384
    Top = 8
  end
  object ChartEditor1: TChartEditor
    Chart = Chart
    Options = [ceTitle]
    TreeView = True
    Left = 456
    Top = 16
  end
end
