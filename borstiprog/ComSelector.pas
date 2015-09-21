unit ComSelector;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls, SerialNG, commportlist;

type
  TForm2 = class(TForm)
    Panel1: TPanel;
    Button1: TButton;
    ComboBox1: TComboBox;
    Label1: TLabel;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private-Deklarationen }
  public
    { Public-Deklarationen }
  end;

var
  Form2: TForm2;

implementation

{$R *.DFM}

procedure TForm2.Button1Click(Sender: TObject);
begin
 Form2.close;
end;

procedure TForm2.FormCreate(Sender: TObject);
begin
 GetPortList(ComboBox1.Items);
end;

end.
