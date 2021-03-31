object PlotControl: TPlotControl
  Left = 743
  Top = 226
  Width = 149
  Height = 267
  Caption = 'Rate of Graphics Update'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  OnClick = FormClick
  PixelsPerInch = 96
  TextHeight = 13
  object PlotUpdate: TRadioGroup
    Left = 0
    Top = 0
    Width = 133
    Height = 228
    Hint = 'Graph'
    Align = alClient
    Caption = 'Plot update Rate'
    ItemIndex = 3
    Items.Strings = (
      'continue'
      'terminate run immediately'
      'daily update'
      'bi-weekly update'
      'weekly update'
      'monthly update'
      'yearly update'
      'update at end of run only')
    TabOrder = 0
    OnClick = PlotUpdateClick
  end
end
