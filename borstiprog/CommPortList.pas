unit CommPortList;
// DomIS Internet Solutions http://www.domis.de
// This Source is distributed under the terms of GNU Licence
// This mean You can use this Source free for Open-Source development
// Additionally I allow the use for inhouse Projects
// It is prohibited to use this source for military Products!!!
// If You want to make a Closed-Source Project with this Source, please contact me
// Any changes should be marked and this header should remain here

interface

uses Windows, Classes;

function CheckOS(var VersionInfo : TOSVersionInfo) : Integer;
procedure GetPortList(Strings : TStrings);

implementation
{$BOOLEVAL OFF}
uses Registry,SysUtils;

function CheckOS(var VersionInfo : TOSVersionInfo) : Integer;
begin
{
    dwOSVersionInfoSize: DWORD;
    dwMajorVersion: DWORD;
    dwMinorVersion: DWORD;
    dwBuildNumber: DWORD;
    dwPlatformId: DWORD;
    szCSDVersion: array[0..127] of AnsiChar; // Maintenance string for PSS usage
}
  VersionInfo.dwOSVersionInfoSize := SizeOf(VersionInfo);
  if GetVersionEx(VersionInfo) then
    CheckOS := VersionInfo.dwPlatformId
  else
    CheckOS := -1;
end;



procedure GetPortList(Strings : TStrings);
var Reg : TRegistry;

  procedure ScanRegHardware;
  var
    i : integer;
    PortName : string;
    LName : TStringList;
  begin
    if Reg.OpenKeyReadOnly('\hardware\devicemap\serialcomm') then
      begin
        LName := TStringList.Create;
        Reg.GetValueNames(LName);
        for i := 0 to LName.Count - 1 do
          begin
            if Reg.GetDataType(LName.Strings[i]) = rdString then
              begin
                PortName := Reg.ReadString(LName.Strings[i]);
                if Strings.IndexOf(PortName) < 0 then
                  Strings.Add(PortName);
              end
          end;
        LName.Free;
      end
  end;

  procedure ScanRegEnum(Key : String);
  // This Subprocedure recurses thru all keys below key
  var
    LKey : TStringList;
    LName : TStringList;
    i : Integer;
    Driver, PortName : String;
    PortSubClass : Byte;
  begin
    if not Reg.OpenKeyReadOnly(Key) then // Danke Andreas Schmidt!
      Exit;
    LName := TStringList.Create;
    Reg.GetValueNames(LName);
    i := LName.IndexOf('class');
    if i >= 0 then
      begin
        if (Reg.GetDataType('class') = rdString) and
           ((LowerCase(Reg.ReadString('class')) = 'ports') or    //normal Serialports like COMx
            (LowerCase(Reg.ReadString('class')) = 'modem')) and  //some abnormal onboard Modems
           (Reg.GetDataType('driver') = rdString) and
           (Reg.GetDataType('portname') = rdString) then
          begin
            Driver := Reg.ReadString('driver');
            PortName := Reg.ReadString('portname');
            if Reg.OpenKeyReadOnly('\System\CurrentControlSet\Services\Class\'+ Driver) and
               (Reg.ReadBinaryData('PortSubClass',PortSubClass,1) = 1) and
               ((PortSubClass = 1) or    //Ports
                (PortSubClass = 2)) and  //Modems
               (Strings.IndexOf(PortName) < 0) then
                 Strings.Add(PortName);
          end
      end;
    LName.Free;
    Reg.OpenKeyReadOnly(Key);
    if Reg.HasSubKeys then
      begin
        LKey := TStringList.Create;
        Reg.GetKeyNames(LKey);
        for i := 0 to LKey.Count - 1 do
          begin
            ScanRegEnum(Key + '\' + LKey[i]);
          end;
        LKey.Free;
      end;
  end;

var
  VersionInfo : TOSVersionInfo;
begin
  if CheckOS(VersionInfo) > 0 then
    if VersionInfo.dwMajorVersion >= 4 then
      begin
        Reg := TRegistry.Create;
        Reg.RootKey := HKEY_LOCAL_MACHINE;
        if VersionInfo.dwMajorVersion > 4 then
          ScanRegHardware //Win 2k, XP
        else if VersionInfo.dwMinorVersion > 0 then
          ScanRegEnum('\enum') //Win9x, mE
        else
          ScanRegHardware; //WinNT
        Reg.Free;
      end;
end;

end.
