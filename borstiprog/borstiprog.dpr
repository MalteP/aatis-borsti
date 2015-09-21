program borstiprog;

uses
  Forms,
  prog in 'prog.pas' {Form1},
  ComSelector in 'ComSelector.pas' {Form2},
  RemoteAnalyze in 'RemoteAnalyze.pas' {Form3};

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.CreateForm(TForm2, Form2);
  Application.CreateForm(TForm3, Form3);
  Application.Run;
end.
