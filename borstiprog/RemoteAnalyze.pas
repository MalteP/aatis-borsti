unit RemoteAnalyze;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls;

type
  TForm3 = class(TForm)
    Panel1: TPanel;
    Button1: TButton;
    Label1: TLabel;
    Memo1: TMemo;
    procedure Button1Click(Sender: TObject);
  private
    { Private-Deklarationen }
  public
    { Public-Deklarationen }
  end;

var
  Form3: TForm3;

implementation

{$R *.DFM}

procedure TForm3.Button1Click(Sender: TObject);
begin
 Form3.hide;
end;

end.
