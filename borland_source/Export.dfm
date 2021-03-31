object FileOutput: TFileOutput
  Left = 635
  Top = 235
  Width = 800
  Height = 508
  Caption = 'File Output'
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
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 289
    Height = 449
    Align = alLeft
    TabOrder = 0
    object Panel2: TPanel
      Left = 1
      Top = 1
      Width = 287
      Height = 24
      Align = alTop
      TabOrder = 0
      object Label2: TLabel
        Left = 197
        Top = 8
        Width = 42
        Height = 13
        Alignment = taCenter
        Caption = 'Selected'
      end
      object Label1: TLabel
        Left = 40
        Top = 8
        Width = 38
        Height = 13
        Alignment = taCenter
        Caption = 'Choices'
      end
    end
    object Panel3: TPanel
      Left = 1
      Top = 336
      Width = 287
      Height = 112
      Align = alBottom
      TabOrder = 1
      object Button1: TButton
        Left = 110
        Top = 23
        Width = 83
        Height = 33
        HelpContext = 1403
        Caption = 'Preview/More'
        TabOrder = 0
        OnClick = Button1Click
      end
      object Button2: TButton
        Left = 72
        Top = 71
        Width = 153
        Height = 33
        HelpContext = 1404
        Caption = 'Excel'
        TabOrder = 1
        OnClick = Button2Click
      end
    end
    object Panel4: TPanel
      Left = 1
      Top = 25
      Width = 287
      Height = 311
      Align = alClient
      TabOrder = 2
      object ListBox2: TListBox
        Left = 156
        Top = 1
        Width = 130
        Height = 309
        HelpContext = 1402
        Align = alRight
        ItemHeight = 13
        MultiSelect = True
        TabOrder = 0
        OnClick = ListBox2Click
      end
      object ListBox1: TListBox
        Left = 1
        Top = 1
        Width = 130
        Height = 309
        HelpContext = 1401
        Align = alLeft
        ItemHeight = 13
        MultiSelect = True
        Sorted = True
        TabOrder = 1
        OnClick = ListBox1Click
      end
    end
  end
  object Panel5: TPanel
    Left = 289
    Top = 0
    Width = 495
    Height = 449
    Align = alClient
    TabOrder = 1
    object Memo1: TMemo
      Left = 1
      Top = 1
      Width = 493
      Height = 447
      HelpContext = 1405
      Align = alClient
      Lines.Strings = (
        '')
      ScrollBars = ssBoth
      TabOrder = 0
    end
  end
  object MainMenu1: TMainMenu
    Left = 48
    Top = 200
    object FileMenu: TMenuItem
      Caption = '&File'
      HelpContext = 1420
      object Save: TMenuItem
        Caption = '&Save'
        OnClick = SaveClick
      end
      object SaveAs: TMenuItem
        Caption = 'Save&As'
        OnClick = SaveAsClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Exit: TMenuItem
        Caption = 'E&xit'
        OnClick = ExitClick
      end
    end
  end
  object SaveDialog1: TSaveDialog
    Filter = 'MMS Files (*.mms)|*mms'
    InitialDir = 'c:/Chm_mms'
    Left = 40
    Top = 120
  end
end
