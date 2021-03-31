object FormEntry: TFormEntry
  Left = 174
  Top = 111
  Width = 951
  Height = 480
  Caption = 'Macro Edit'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  OnActivate = FormActivate
  OnDeactivate = FormDeactivate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 935
    Height = 422
    Align = alClient
    TabOrder = 0
    object Panel2: TPanel
      Left = 1
      Top = 1
      Width = 918
      Height = 347
      Align = alClient
      TabOrder = 0
      object Memo: TMemo
        Left = 1
        Top = 1
        Width = 916
        Height = 345
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        ScrollBars = ssBoth
        TabOrder = 0
        WantReturns = False
        WordWrap = False
      end
      object MemoFile: TMemo
        Left = 192
        Top = 128
        Width = 57
        Height = 33
        Lines.Strings = (
          '')
        TabOrder = 1
        Visible = False
        WantReturns = False
        WordWrap = False
      end
    end
    object Panel3: TPanel
      Left = 919
      Top = 1
      Width = 15
      Height = 347
      Align = alRight
      TabOrder = 1
    end
    object Panel4: TPanel
      Left = 1
      Top = 348
      Width = 933
      Height = 73
      Align = alBottom
      TabOrder = 2
      object SaveChanges: TButton
        Left = 64
        Top = 24
        Width = 89
        Height = 33
        Caption = 'Save Changes'
        TabOrder = 0
        OnClick = SaveChangesClick
      end
      object CancelChanges: TButton
        Left = 208
        Top = 24
        Width = 89
        Height = 33
        Caption = 'Cancel Changes'
        TabOrder = 1
        OnClick = CancelChangesClick
      end
    end
  end
  object MainMenu: TMainMenu
    Left = 168
    Top = 16
    object File: TMenuItem
      Caption = '&File'
      object Open: TMenuItem
        Caption = '&Open'
        OnClick = OpenClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Save: TMenuItem
        Caption = '&Save'
        OnClick = SaveClick
      end
      object SaveAs: TMenuItem
        Caption = 'Save&As'
        OnClick = SaveAsClick
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object CreateGroup1: TMenuItem
        Caption = 'CreateGroup'
        OnClick = CreateGroup1Click
      end
      object N4: TMenuItem
        Caption = '-'
      end
      object Clear1: TMenuItem
        Caption = 'Clear'
        OnClick = ClearClick
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object Exit: TMenuItem
        Caption = 'E&xit'
        OnClick = ExitClick
      end
    end
  end
  object SaveDialogMcr: TSaveDialog
    Left = 256
    Top = 56
  end
  object OpenDialogMcr: TOpenDialog
    Left = 328
    Top = 40
  end
  object SaveDialogPar: TSaveDialog
    Left = 520
    Top = 80
  end
end
