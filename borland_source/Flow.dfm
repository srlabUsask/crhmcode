object FlowForm: TFlowForm
  Left = 203
  Top = 199
  Width = 844
  Height = 545
  HorzScrollBar.ButtonSize = 10
  HorzScrollBar.Increment = 20
  HorzScrollBar.Position = 24
  HorzScrollBar.Range = 844
  HorzScrollBar.Tracking = True
  VertScrollBar.ButtonSize = 10
  VertScrollBar.Increment = 20
  VertScrollBar.Range = 545
  AutoScroll = False
  Caption = 'FlowForm'
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
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  OnKeyUp = FormKeyUp
  OnPaint = FormPaint
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object StringGrid1: TStringGrid
    Left = -24
    Top = 0
    Width = 844
    Height = 545
    Align = alClient
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
    TabOrder = 0
  end
  object MainMenu1: TMainMenu
    Left = 112
    Top = 8
    object File1: TMenuItem
      Caption = '&File'
      object Print1: TMenuItem
        Caption = '&Print'
        OnClick = Print1Click
      end
      object PrinterSetUp1: TMenuItem
        Caption = 'Printer &SetUp'
        OnClick = PrinterSetUp1Click
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = 'E&xit'
        OnClick = Exit1Click
      end
    end
    object Copy1: TMenuItem
      Caption = '&Copy'
      object BitFile1: TMenuItem
        Caption = '&BitFile'
        OnClick = BitFile1Click
      end
      object MetaFile1: TMenuItem
        Caption = '&MetaFile'
        OnClick = MetaFile1Click
      end
    end
    object Selection1: TMenuItem
      Caption = '&Selection'
      OnClick = Selection1Click
    end
  end
  object PrinterSetupDialog1: TPrinterSetupDialog
    Left = 264
    Top = 96
  end
  object PrintDialog1: TPrintDialog
    Left = 200
    Top = 72
  end
  object FontDialog1: TFontDialog
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    MinFontSize = 0
    MaxFontSize = 0
    Left = 320
    Top = 48
  end
end
