object LogForm: TLogForm
  Left = 1
  Top = 1
  Width = 798
  Height = 554
  Caption = 'Log'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnActivate = FormActivate
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 790
    Height = 508
    Align = alClient
    Caption = 'Panel1'
    Constraints.MinWidth = 250
    TabOrder = 0
    object Panel2: TPanel
      Left = 1
      Top = 1
      Width = 788
      Height = 240
      Align = alTop
      Caption = 'Panel2'
      TabOrder = 0
      object Panel4: TPanel
        Left = 1
        Top = 1
        Width = 786
        Height = 25
        Align = alTop
        TabOrder = 0
        object LabelLog: TLabel
          Left = 1
          Top = 1
          Width = 784
          Height = 16
          Align = alTop
          Alignment = taCenter
          Caption = 'Warnings and Errors'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
      end
      object Panel6: TPanel
        Left = 1
        Top = 26
        Width = 786
        Height = 213
        Align = alClient
        Caption = 'Panel6'
        TabOrder = 1
        object MemoLog: TMemo
          Left = 1
          Top = 1
          Width = 784
          Height = 211
          HelpContext = 1601
          Align = alClient
          ScrollBars = ssVertical
          TabOrder = 0
          OnEnter = MemoLogEnter
        end
      end
    end
    object Panel3: TPanel
      Left = 1
      Top = 241
      Width = 788
      Height = 266
      Align = alClient
      Caption = 'Panel3'
      Constraints.MinHeight = 200
      TabOrder = 1
      object Panel5: TPanel
        Left = 1
        Top = 1
        Width = 786
        Height = 25
        Align = alTop
        TabOrder = 0
        object LabelDebug: TLabel
          Left = 1
          Top = 1
          Width = 784
          Height = 16
          Align = alTop
          Alignment = taCenter
          Caption = 'Debug Output'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
      end
      object Panel7: TPanel
        Left = 1
        Top = 26
        Width = 786
        Height = 239
        Align = alClient
        Caption = 'Panel7'
        TabOrder = 1
        object MemoDebug: TMemo
          Left = 1
          Top = 1
          Width = 784
          Height = 237
          HelpContext = 1602
          Align = alClient
          Lines.Strings = (
            '')
          ScrollBars = ssVertical
          TabOrder = 0
          OnEnter = MemoDebugEnter
        end
      end
    end
  end
  object MainMenu1: TMainMenu
    Left = 168
    Top = 64
    object File: TMenuItem
      Caption = '&File'
      HelpContext = 1620
      object FileSave: TMenuItem
        Caption = '&Save'
        OnClick = FileSaveClick
      end
      object FileSaveAs: TMenuItem
        Caption = 'Save&As'
        OnClick = FileSaveAsClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Print1: TMenuItem
        Caption = '&Print'
        OnClick = Print1Click
      end
      object PrinterSetup1: TMenuItem
        Caption = 'Printer &Setup'
        OnClick = PrinterSetup1Click
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Font1: TMenuItem
        Caption = '&Font'
        OnClick = Font1Click
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = '&Exit'
        OnClick = Exit1Click
      end
    end
    object Clear: TMenuItem
      Caption = '&Clear'
      object ClearErrors: TMenuItem
        Caption = '&Errors'
        OnClick = ClearErrorsClick
      end
      object ClearDebug: TMenuItem
        Caption = '&Debug'
        OnClick = ClearDebugClick
      end
    end
    object Flags1: TMenuItem
      Caption = 'Parameters (integer)'
      OnClick = Flags1Click
    end
    object Coefficients1: TMenuItem
      Caption = 'Coefficients (ending '#39'_K'#39')'
      OnClick = Coefficients1Click
    end
    object Parameters1: TMenuItem
      Caption = 'Parameters (float)'
      OnClick = Parameters1Click
    end
  end
  object SaveDialog1: TSaveDialog
    Left = 304
    Top = 104
  end
end
