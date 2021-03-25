object Rprt: TRprt
  Left = 489
  Top = 185
  Width = 800
  Height = 501
  Caption = 'Summary'
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
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel3: TPanel
    Left = 0
    Top = 0
    Width = 784
    Height = 443
    Align = alClient
    Caption = 'Panel3'
    TabOrder = 0
    object Panel1: TPanel
      Left = 1
      Top = 1
      Width = 650
      Height = 441
      Align = alLeft
      Caption = 'Panel1'
      TabOrder = 0
      object Memo1: TMemo
        Left = 1
        Top = 1
        Width = 648
        Height = 439
        Align = alClient
        Lines.Strings = (
          '')
        ScrollBars = ssBoth
        TabOrder = 0
        WordWrap = False
      end
      object Edit: TEdit
        Left = 360
        Top = 24
        Width = 200
        Height = 24
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        Text = 'Edit'
        Visible = False
        OnKeyPress = EditKeyPress
      end
    end
    object Panel2: TPanel
      Left = 651
      Top = 1
      Width = 132
      Height = 441
      Align = alClient
      Caption = 'Panel2'
      TabOrder = 1
      object Label1: TLabel
        Left = 1
        Top = 1
        Width = 130
        Height = 13
        Align = alTop
        Alignment = taCenter
        OnClick = Label1Click
      end
      object ListBox1: TListBox
        Left = 1
        Top = 14
        Width = 130
        Height = 426
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Pitch = fpFixed
        Font.Style = []
        ItemHeight = 13
        ParentFont = False
        TabOrder = 0
        OnClick = ListBox1Click
      end
    end
  end
  object MainMenu1: TMainMenu
    Left = 56
    Top = 32
    object File1: TMenuItem
      Caption = '&File'
      object Save1: TMenuItem
        Caption = '&Save'
        OnClick = Save1Click
      end
      object SaveAs1: TMenuItem
        Caption = 'Save&As'
        OnClick = SaveAs1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Print1: TMenuItem
        Caption = '&Print'
        OnClick = Print1Click
      end
      object PrintSetup1: TMenuItem
        Caption = 'Print &Setup'
        OnClick = PrintSetup1Click
      end
      object N3: TMenuItem
        Caption = '-'
      end
      object Font1: TMenuItem
        Caption = '&Font'
        OnClick = Font1Click
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = 'E&xit'
        OnClick = Exit1Click
      end
    end
    object Execution1: TMenuItem
      Caption = 'Execution'
      Enabled = False
      object Mapvars: TMenuItem
        Caption = 'Mapvars'
        OnClick = MapvarsClick
      end
      object Mapvarsget1: TMenuItem
        Caption = 'Mapvarsget'
        OnClick = Mapvarsget1Click
      end
      object Mapvarsput1: TMenuItem
        Caption = 'Mapvarsput'
        OnClick = Mapvarsput1Click
      end
      object Mapobsget1: TMenuItem
        Caption = 'Mapobsget'
        OnClick = Mapobsget1Click
      end
      object Mappars: TMenuItem
        Caption = 'Mappars'
        OnClick = MapparsClick
      end
      object MapSharedpars1: TMenuItem
        Caption = 'MapSharedpars'
        OnClick = MapSharedpars1Click
      end
    end
    object Chart1: TMenuItem
      Caption = 'Chart'
      Enabled = False
      OnClick = Chart1Click
    end
    object Bld1: TMenuItem
      Caption = 'Bld'
      Enabled = False
      object declvar1: TMenuItem
        Caption = 'declvar'
        OnClick = declvar1Click
      end
      object getvar1: TMenuItem
        Caption = 'getvar'
        OnClick = getvar1Click
      end
      object putvar1: TMenuItem
        Caption = 'putvar'
        OnClick = putvar1Click
      end
      object readvar1: TMenuItem
        Caption = 'readvar'
        OnClick = readvar1Click
      end
      object declobs1: TMenuItem
        Caption = 'declobs'
        OnClick = declobs1Click
      end
      object declpar1: TMenuItem
        Caption = 'declpar'
        OnClick = declpar1Click
      end
      object declstat1: TMenuItem
        Caption = 'declstat'
        OnClick = declstat1Click
      end
      object AKA1: TMenuItem
        Caption = 'AKA'
        OnClick = AKA1Click
      end
    end
    object Lists1: TMenuItem
      Caption = 'Lists'
      Enabled = False
      object AllModulesList1: TMenuItem
        Caption = 'AllModulesList'
        OnClick = AllModulesList1Click
      end
      object OurModulesList1: TMenuItem
        Caption = 'OurModulesList'
        OnClick = OurModulesList1Click
      end
      object MacroModulesList1: TMenuItem
        Caption = 'MacroModulesList'
        OnClick = MacroModulesList1Click
      end
      object DeclRootList1: TMenuItem
        Caption = 'DeclRootList'
        OnClick = DeclRootList1Click
      end
    end
    object Global1: TMenuItem
      Caption = 'Global'
      Enabled = False
      OnClick = Global1Click
    end
    object AKA2: TMenuItem
      Caption = 'AKA'
      Enabled = False
      OnClick = AKA2Click
    end
    object RenameGroup: TMenuItem
      Caption = 'RenameGroup'
      Enabled = False
      OnClick = RenameGroupClick
    end
    object Hierarchy1: TMenuItem
      Caption = 'Hierarchy'
      OnClick = Hierarchy1Click
    end
    object ExtractGroup: TMenuItem
      Caption = 'ExtractGroup'
      OnClick = ExtractGroupClick
    end
    object Extras1: TMenuItem
      Caption = 'Extras'
      object CheckNan1: TMenuItem
        Caption = 'NaN_check OFF'
        OnClick = CheckNan1Click
      end
      object LOGVARLOAD1: TMenuItem
        Caption = 'LogVarLoad OFF'
        OnClick = LOGVARLOAD1Click
      end
      object LogTimeFormat1: TMenuItem
        Caption = 'Log Time Format'
        object MSTime1: TMenuItem
          Caption = 'MS Time'
          OnClick = MSTime1Click
        end
        object MMDDYYYY1: TMenuItem
          Caption = 'MM/DD/YYYY'
          OnClick = MMDDYYYY1Click
        end
        object YYYYMMDD1: TMenuItem
          Caption = 'YYYY-MM-DD'
          OnClick = YYYYMMDD1Click
        end
      end
    end
  end
  object SaveDialog1: TSaveDialog
    Left = 40
    Top = 120
  end
end
