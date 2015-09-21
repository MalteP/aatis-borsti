unit prog;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ExtCtrls, Menus, SerialNG, ComCtrls, IniFiles;

type
  TForm1 = class(TForm)
    Panel1: TPanel;
    Edit1: TEdit;
    Label1: TLabel;
    Edit2: TEdit;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Edit3: TEdit;
    Edit4: TEdit;
    Edit5: TEdit;
    Edit6: TEdit;
    Edit7: TEdit;
    Edit8: TEdit;
    Edit9: TEdit;
    Edit10: TEdit;
    Edit11: TEdit;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Edit12: TEdit;
    Edit13: TEdit;
    Edit14: TEdit;
    Edit15: TEdit;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Edit16: TEdit;
    Label15: TLabel;
    Edit17: TEdit;
    Label16: TLabel;
    MainMenu1: TMainMenu;
    Datei1: TMenuItem;
    Beenden1: TMenuItem;
    Port1: TMenuItem;
    SerialPortNG1: TSerialPortNG;
    Auswahl1: TMenuItem;
    Verbinden1: TMenuItem;
    Button2: TButton;
    Button1: TButton;
    StatusBar1: TStatusBar;
    Trennen1: TMenuItem;
    TrackBar1: TTrackBar;
    EinstellungenLaden1: TMenuItem;
    Presetspeichern1: TMenuItem;
    N1: TMenuItem;
    Zurcksetzen1: TMenuItem;
    Label14: TLabel;
    Label17: TLabel;
    Label18: TLabel;
    Label19: TLabel;
    OpenDialog1: TOpenDialog;
    SaveDialog1: TSaveDialog;
    Timer1: TTimer;
    Extras1: TMenuItem;
    Fernbedienunganalysieren1: TMenuItem;
    procedure Beenden1Click(Sender: TObject);
    procedure Auswahl1Click(Sender: TObject);
    procedure Verbinden1Click(Sender: TObject);
    procedure Trennen1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure TrackBar1Change(Sender: TObject);
    procedure Zurcksetzen1Click(Sender: TObject);
    procedure EinstellungenLaden1Click(Sender: TObject);
    procedure Presetspeichern1Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure SerialPortNG1RxClusterEvent(Sender: TObject);
    procedure Fernbedienunganalysieren1Click(Sender: TObject);
  private
    { Private-Deklarationen }
  public
    { Public-Deklarationen }
  end;

var
  Form1: TForm1;
  connected: Integer;
  state_timeout: Integer;
  state_pos: Integer;
  field_pos: Integer;
  rcv_buffer: String;
  rcv_temp: String;
  snd_temp: String;

procedure ResetValues; forward;

implementation

uses ComSelector, RemoteAnalyze;

{$R *.DFM}

procedure TForm1.Beenden1Click(Sender: TObject);
begin
 close;
end;

procedure TForm1.Auswahl1Click(Sender: TObject);
begin
 Form2.show;
end;

procedure TForm1.Verbinden1Click(Sender: TObject);
begin
 if Form2.ComboBox1.Text = '' then
  begin
   StatusBar1.Panels[0].Text := 'Fehler: Kein COM Port gewählt!';
  end
 else
  begin
   SerialPortNG1.CommPort := Form2.ComboBox1.Text;
   SerialPortNG1.BaudRate := 38400;
   SerialPortNG1.DataBits := 8;
   SerialPortNG1.StopBits := 0;
   SerialPortNG1.ParityType := 0;
   SerialPortNG1.FlowControl := 0;
   SerialPortNG1.Active := true;
   StatusBar1.Panels[0].Text := 'Verbunden auf '+Form2.ComboBox1.Text;
  end;
end;

procedure TForm1.Trennen1Click(Sender: TObject);
begin
   SerialPortNG1.Active := false;
 StatusBar1.Panels[0].Text := 'Nicht verbunden.';
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
 ResetValues;
 StatusBar1.Panels[0].Text := 'Nicht verbunden.';
end;

procedure ResetValues;
begin
 Form1.Edit1.Text := '02';
 Form1.Edit2.Text := 'BD';
 Form1.Edit3.Text := '00';
 Form1.Edit4.Text := '15';
 Form1.Edit5.Text := '06';
 Form1.Edit6.Text := '08';
 Form1.Edit7.Text := '07';
 Form1.Edit8.Text := '1C';
 Form1.Edit9.Text := '09';
 Form1.Edit10.Text := '01';
 Form1.Edit11.Text := '02';
 Form1.Edit12.Text := '11';
 Form1.Edit13.Text := '12';
 Form1.Edit14.Text := '10';
 Form1.Edit15.Text := 'FF';
 Form1.Edit16.Text := 'FF';
 Form1.Edit17.Text := '';
 Form1.TrackBar1.Position := 0;
end;

procedure TForm1.TrackBar1Change(Sender: TObject);
begin
 if TrackBar1.Position > 0 then
  begin
   Edit15.text := IntToHex(255-TrackBar1.Position, 2);
   Edit16.text := IntToHex(255, 2);
  end
 else
  begin
   Edit15.text := IntToHex(255, 2);
   Edit16.text := IntToHex(255+TrackBar1.Position, 2);
  end;
end;

procedure TForm1.Zurcksetzen1Click(Sender: TObject);
begin
 ResetValues;
end;

procedure TForm1.EinstellungenLaden1Click(Sender: TObject);
var
 ini: TIniFile;
begin
  if openDialog1.Execute then
  begin
   ini := TIniFile.Create(openDialog1.FileName);
   Form1.Edit1.Text := ini.ReadString('Remote', 'Addr_L', 'FF');
   Form1.Edit2.Text := ini.ReadString('Remote', 'Addr_H', 'FF');
   Form1.Edit3.Text := ini.ReadString('Remote', 'Toggle_Front', 'FF');
   Form1.Edit4.Text := ini.ReadString('Remote', 'Beep', 'FF');
   Form1.Edit5.Text := ini.ReadString('Remote', 'Blink_L', 'FF');
   Form1.Edit6.Text := ini.ReadString('Remote', 'Blink_R', 'FF');
   Form1.Edit7.Text := ini.ReadString('Remote', 'Blink_N', 'FF');
   Form1.Edit8.Text := ini.ReadString('Remote', 'Blink_W', 'FF');
   Form1.Edit9.Text := ini.ReadString('Remote', 'Blink_A', 'FF');
   Form1.Edit10.Text := ini.ReadString('Remote', 'Flash_F', 'FF');
   Form1.Edit11.Text := ini.ReadString('Remote', 'Flash_O', 'FF');
   Form1.Edit12.Text := ini.ReadString('Remote', 'Motor_L', 'FF');
   Form1.Edit13.Text := ini.ReadString('Remote', 'Motor_S', 'FF');
   Form1.Edit14.Text := ini.ReadString('Remote', 'Motor_R', 'FF');
   Form1.Edit15.Text := ini.ReadString('Motor', 'Bal_R', 'FF');
   Form1.Edit16.Text := ini.ReadString('Motor', 'Bal_L', 'FF');
   Form1.Edit17.Text := ini.ReadString('Bluetooth', 'Name', '');
   ini.Free;
  end
end;

procedure TForm1.Presetspeichern1Click(Sender: TObject);
var
 ini: TIniFile;
begin
  if saveDialog1.Execute then
  begin
   ini := TIniFile.Create(saveDialog1.FileName);
   ini.WriteString('Remote', 'Addr_L', Form1.Edit1.Text);
   ini.WriteString('Remote', 'Addr_H', Form1.Edit2.Text);
   ini.WriteString('Remote', 'Toggle_Front', Form1.Edit3.Text);
   ini.WriteString('Remote', 'Beep', Form1.Edit4.Text);
   ini.WriteString('Remote', 'Blink_L', Form1.Edit5.Text);
   ini.WriteString('Remote', 'Blink_R', Form1.Edit6.Text);
   ini.WriteString('Remote', 'Blink_N', Form1.Edit7.Text);
   ini.WriteString('Remote', 'Blink_W', Form1.Edit8.Text);
   ini.WriteString('Remote', 'Blink_A', Form1.Edit9.Text);
   ini.WriteString('Remote', 'Flash_F', Form1.Edit10.Text);
   ini.WriteString('Remote', 'Flash_O', Form1.Edit11.Text);
   ini.WriteString('Remote', 'Motor_L', Form1.Edit12.Text);
   ini.WriteString('Remote', 'Motor_S', Form1.Edit13.Text);
   ini.WriteString('Remote', 'Motor_R', Form1.Edit14.Text);
   ini.WriteString('Motor', 'Bal_R', Form1.Edit15.Text);
   ini.WriteString('Motor', 'Bal_L', Form1.Edit16.Text);
   ini.WriteString('Bluetooth', 'Name', Form1.Edit17.Text);
   ini.Free;
  end
end;

procedure TForm1.Timer1Timer(Sender: TObject);
begin
 // Handle timeout
 if state_timeout > 0 then state_timeout := state_timeout -1 else
  begin
   if state_pos > 0 then StatusBar1.Panels[0].Text := 'Fehler: Timeout...';
   Form1.Fernbedienunganalysieren1.enabled := true;
   Button1.enabled := true;
   Button2.enabled := true;
   state_pos := 0;
  end;
end;

procedure serial_event;
var rx_to: Integer;
begin
 rx_to := 50;
 // Begin state machine
 case state_pos of
  0: // Idle
   begin
   end;
  // **** Load data ****
  1: // Start RX
   begin
    state_timeout := rx_to;
    rcv_buffer := '';
    Form1.SerialPortNG1.SendString('MO2'+#10);
    state_pos := state_pos +1;
   end;
  2: // Mode is 2
   begin
    if rcv_buffer = '+' then
     begin
      state_timeout := rx_to;
      rcv_buffer := '';
      field_pos := 0;
      Form1.StatusBar1.Panels[0].Text := 'Lese '+IntToStr(field_pos)+'/21';
      Form1.SerialPortNG1.SendString('EE?00'+#10);
      state_pos := state_pos +1;
     end;
    end;
  3:
   begin
    if rcv_buffer <> '' then
     begin
      case field_pos of
       0: Form1.Edit1.Text := rcv_buffer;
       1: Form1.Edit2.Text := rcv_buffer;
       2: Form1.Edit3.Text := rcv_buffer;
       3: Form1.Edit4.Text := rcv_buffer;
       4: Form1.Edit5.Text := rcv_buffer;
       5: Form1.Edit6.Text := rcv_buffer;
       6: Form1.Edit7.Text := rcv_buffer;
       7: Form1.Edit8.Text := rcv_buffer;
       8: Form1.Edit9.Text := rcv_buffer;
       9: Form1.Edit10.Text := rcv_buffer;
       10: Form1.Edit11.Text := rcv_buffer;
       11: Form1.Edit12.Text := rcv_buffer;
       12: Form1.Edit13.Text := rcv_buffer;
       13: Form1.Edit14.Text := rcv_buffer;
       14: Form1.Edit15.Text := rcv_buffer;
       15: Form1.Edit16.Text := rcv_buffer;
      end;
      field_pos := field_pos +1;
      state_timeout := rx_to;
      rcv_buffer := '';
      Form1.StatusBar1.Panels[0].Text := 'Lese '+IntToStr(field_pos)+'/21';
      Form1.SerialPortNG1.SendString('EE?'+IntToHex(field_pos, 2)+#10);
      if field_pos > 15 then
       begin
        rcv_temp := '';
        state_pos := state_pos +1;
       end;
     end;
   end;
  4:
   begin
    if StrToInt('$'+rcv_buffer) >= 32 then
     begin
      rcv_temp := rcv_temp + Chr(StrToInt('$'+rcv_buffer));
      field_pos := field_pos +1;
     end else begin
      field_pos := 22;
      Form1.StatusBar1.Panels[0].Text := 'Lese '+IntToStr(field_pos)+'/21';
     end;
    if field_pos <= 21 then
     begin
      state_timeout := rx_to;
      rcv_buffer := '';
      Form1.StatusBar1.Panels[0].Text := 'Lese '+IntToStr(field_pos)+'/21';
      Form1.SerialPortNG1.SendString('EE?'+IntToHex(field_pos, 2)+#10);
     end else begin // Switch back mode
      Form1.Edit17.Text := rcv_temp;
      state_timeout := rx_to;
      rcv_buffer := '';
      Form1.SerialPortNG1.SendString('MO0'+#10);
      state_pos := state_pos +1;
     end;
   end;
  5: // Finish RX
   begin
    if rcv_buffer = '+' then
     begin
      state_pos := 0;
      Form1.StatusBar1.Panels[0].Text := 'Erfolgreich!';
      Form1.Fernbedienunganalysieren1.enabled := true;
      Form1.Button1.enabled := true;
      Form1.Button2.enabled := true;
     end;
   end;
  // **** Write data ****
  6: // Start RX
   begin
    state_timeout := rx_to;
    rcv_buffer := '';
    field_pos := 0;
    Form1.SerialPortNG1.SendString('MO2'+#10);
    state_pos := state_pos +1;
   end;
  7: // Mode is 2
   begin
    if rcv_buffer = '+' then
     begin
      state_timeout := rx_to;
      rcv_buffer := '';
      case field_pos of
       0: snd_temp := Form1.Edit1.Text;
       1: snd_temp := Form1.Edit2.Text;
       2: snd_temp := Form1.Edit3.Text;
       3: snd_temp := Form1.Edit4.Text;
       4: snd_temp := Form1.Edit5.Text;
       5: snd_temp := Form1.Edit6.Text;
       6: snd_temp := Form1.Edit7.Text;
       7: snd_temp := Form1.Edit8.Text;
       8: snd_temp := Form1.Edit9.Text;
       9: snd_temp := Form1.Edit10.Text;
       10: snd_temp := Form1.Edit11.Text;
       11: snd_temp := Form1.Edit12.Text;
       12: snd_temp := Form1.Edit13.Text;
       13: snd_temp := Form1.Edit14.Text;
       14: snd_temp := Form1.Edit15.Text;
       15: snd_temp := Form1.Edit16.Text;
       16,17,18,19,20,21:
        begin
         if Length(Form1.Edit17.Text) >= (field_pos-15) then
          begin
           snd_temp := IntToHex(Ord(Form1.Edit17.Text[(field_pos-15)]), 2);
          end else begin
           snd_temp := '00';
          end;
        end;
      end;
      if field_pos <= 21 then
       begin
        Form1.StatusBar1.Panels[0].Text := 'Schreibe '+IntToStr(field_pos)+'/21';
        Form1.SerialPortNG1.SendString('EE'+IntToHex(field_pos, 2)+snd_temp+#10);
        field_pos := field_pos +1;
       end else begin
        state_timeout := rx_to;
        rcv_buffer := '';
        Form1.SerialPortNG1.SendString('MO0'+#10);
        state_pos := state_pos +1;
       end
     end;
    end;
  8: // Finish TX
   begin
    if rcv_buffer = '+' then
     begin
      state_pos := 0;
      Form1.StatusBar1.Panels[0].Text := 'Erfolgreich!';
      Form1.Fernbedienunganalysieren1.enabled := true;
      Form1.Button1.enabled := true;
      Form1.Button2.enabled := true;
     end;
   end;
  9: // Start fb query mode
   begin
    state_timeout := rx_to;
    rcv_buffer := '';
    Form1.SerialPortNG1.SendString('MO2'+#10);
    state_pos := state_pos +1;
   end;
  10: // Mode is 2
   begin
    if rcv_buffer = '+' then
     begin
      state_timeout := rx_to;
      rcv_buffer := '';
      Form1.StatusBar1.Panels[0].Text := 'Lese Infrarotpuffer...';
      Form1.SerialPortNG1.SendString('IR?'+#10);
      state_pos := state_pos +1;
     end;
   end;
  11:
   begin
    if rcv_buffer <> '-' then
     begin
      if length(rcv_buffer) = 6 then
       begin
        Form3.Memo1.Lines.Add('Adresse Low: '+Copy(rcv_buffer, 0, 2)+', Adresse High: '+Copy(rcv_buffer, 3, 2)+', Tastencode: '+Copy(rcv_buffer, 5, 2));
       end else begin
        Form3.Memo1.Lines.Add('Unerwartete Daten empfangen! Abbruch.');
        state_pos := state_pos +1;
        serial_event;
       end;
     end;
    if state_pos = 11 then // Just check if recieve is not skipped above
     begin
      state_timeout := rx_to;
      rcv_buffer := '';
      Form1.StatusBar1.Panels[0].Text := 'Lese Infrarotpuffer...';
      Form1.SerialPortNG1.SendString('IR?'+#10);
      if Form3.visible = false then state_pos := state_pos +1;
     end;
   end;
  12:
   begin
    state_timeout := rx_to;
    rcv_buffer := '';
    field_pos := 0;
    Form1.SerialPortNG1.SendString('MO0'+#10);
    state_pos := state_pos +1;
   end;
  13: // Finish TX
   begin
    if rcv_buffer = '+' then
     begin
      state_pos := 0;
      Form1.StatusBar1.Panels[0].Text := 'Erfolgreich!';
      Form1.Fernbedienunganalysieren1.enabled := true;
      Form1.Button1.enabled := true;
      Form1.Button2.enabled := true;
     end;
   end;
 end;
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
 if Form2.ComboBox1.Text = '' then
  begin
   StatusBar1.Panels[0].Text := 'Fehler: Kein COM Port gewählt!';
  end
 else
  begin
   Fernbedienunganalysieren1.enabled := false;
   Button1.enabled := false;
   Button2.enabled := false;
   state_pos := 1;
   serial_event;
  end;
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
 if Form2.ComboBox1.Text = '' then
  begin
   StatusBar1.Panels[0].Text := 'Fehler: Kein COM Port gewählt!';
  end
 else
  begin
   Fernbedienunganalysieren1.enabled := false;
   Button1.enabled := false;
   Button2.enabled := false;
   state_pos := 6;
   serial_event;
  end;
end;

procedure TForm1.SerialPortNG1RxClusterEvent(Sender: TObject);
begin
 rcv_buffer := trim(SerialPortNG1.ReadNextClusterAsString);
 serial_event;
end;

procedure TForm1.Fernbedienunganalysieren1Click(Sender: TObject);
begin
 if Form2.ComboBox1.Text = '' then
  begin
   StatusBar1.Panels[0].Text := 'Fehler: Kein COM Port gewählt!';
  end
 else
  begin
   Form3.Memo1.Lines.Clear;
   Fernbedienunganalysieren1.enabled := false;
   Button1.enabled := false;
   Button2.enabled := false;
   state_pos := 9;
   serial_event;
   Form3.show;
  end;
end;

end.
