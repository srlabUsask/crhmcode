object FormAKA: TFormAKA
  Left = 39
  Top = 210
  Width = 1074
  Height = 737
  Caption = 'Module customization'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnActivate = FormActivate
  OnDeactivate = FormDeactivate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1066
    Height = 185
    Align = alTop
    Caption = 'Panel1'
    TabOrder = 0
    object RadioGroup: TRadioGroup
      Left = 1
      Top = 1
      Width = 128
      Height = 183
      Align = alLeft
      Caption = 'Model quantities'
      ItemIndex = 1
      Items.Strings = (
        'Variables'
        'Observations')
      TabOrder = 0
      OnClick = RadioGroupClick
    end
    object Memo: TMemo
      Left = 129
      Top = 1
      Width = 456
      Height = 183
      Align = alLeft
      TabOrder = 1
      WordWrap = False
      OnDblClick = MemoDblClick
    end
    object ListBox1: TListBox
      Left = 585
      Top = 1
      Width = 480
      Height = 183
      Align = alClient
      ItemHeight = 13
      MultiSelect = True
      TabOrder = 2
      OnClick = ListBox1Click
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 185
    Width = 1066
    Height = 498
    Align = alClient
    Caption = 'Panel3'
    TabOrder = 1
    object Panel4: TPanel
      Left = 1
      Top = 448
      Width = 1064
      Height = 49
      Align = alBottom
      TabOrder = 0
      object Save1: TButton
        Left = 8
        Top = 4
        Width = 91
        Height = 41
        Caption = 'Save to Model'
        TabOrder = 0
        OnClick = Save1Click
      end
      object RemoveUnused: TButton
        Left = 117
        Top = 4
        Width = 91
        Height = 41
        Caption = 'Remove Unused'
        TabOrder = 1
        OnClick = RemoveUnusedClick
      end
      object Void: TButton
        Left = 226
        Top = 4
        Width = 91
        Height = 41
        Caption = 'Void Changes'
        TabOrder = 2
        OnClick = VoidClick
      end
      object Escape: TButton
        Left = 336
        Top = 4
        Width = 91
        Height = 41
        Caption = 'Escape'
        TabOrder = 3
        OnClick = EscapeClick
      end
    end
    object StringGrid1: TStringGrid
      Left = 1
      Top = 1
      Width = 1064
      Height = 447
      Align = alClient
      DefaultColWidth = 120
      TabOrder = 1
      OnGetEditText = StringGrid1GetEditText
      OnKeyPress = StringGrid1KeyPress
      OnMouseDown = StringGrid1MouseDown
      OnSelectCell = StringGrid1SelectCell
      OnSetEditText = StringGrid1SetEditText
      ColWidths = (
        120
        120
        84
        63
        120)
    end
  end
  object MainMenu1: TMainMenu
    Left = 208
    Top = 32
    object File: TMenuItem
      Caption = 'File'
      object Open1: TMenuItem
        Caption = '&Open'
        OnClick = Open1Click
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
      object Exit: TMenuItem
        Caption = '&Exit'
        OnClick = ExitClick
      end
    end
  end
  object OpenDialogAKA: TOpenDialog
    Left = 200
    Top = 104
  end
  object SaveDialogAKA: TSaveDialog
    Left = 224
    Top = 168
  end
end
