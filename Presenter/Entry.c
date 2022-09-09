#include <Presenter/Entry.h>
#include <Protocol/SimpleTextIn.h>
#include <Library/UefiMouseLib/UefiMouseLib.h>
#define SHELL_PROMPT L"Baby Shell> "
#define STR_COMMAND_LINE_SIZE 1024

void StartMySystem(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable){
    InitMouseSPP(SystemTable);
    
}
void ShellForTest(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable){
    EFI_INPUT_KEY key;
    unsigned short str[3];
    unsigned short str_command_line[STR_COMMAND_LINE_SIZE];
    unsigned int str_command_line_pos = 0;
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    SystemTable->ConOut->OutputString(SystemTable->ConOut,SHELL_PROMPT);
    while(1){
        
        if (!SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn,&key)){
            if (key.UnicodeChar != L'\r'){
                str[0] = key.UnicodeChar;
                str[1] = L'\0';
                Print(L"%d\n",str[0]);
                if (str_command_line_pos < STR_COMMAND_LINE_SIZE - 1){
                    str_command_line[str_command_line_pos] = key.UnicodeChar;
                    str_command_line[str_command_line_pos + 1] = L'\0';
                    SystemTable->ConOut->OutputString(SystemTable->ConOut,str);
                    str_command_line_pos++;
                }else{
                    SystemTable->ConOut->OutputString(SystemTable->ConOut,L"Too Long Command cause overflow!");
                    str_command_line_pos = 0;
                }
            }else{
                str[0] = L'\r';
                str[1] = L'\n';
                str[2] = L'\0';
                SystemTable->ConOut->OutputString(SystemTable->ConOut,str);
                if (!StrCmp(str_command_line,L"ping")){
                    SystemTable->ConOut->OutputString(SystemTable->ConOut,L"pong!\r\n\0");
                }
                if (!StrCmp(str_command_line,L"start")){
                    StartMySystem(ImageHandle,SystemTable);
                }
                SystemTable->ConOut->OutputString(SystemTable->ConOut,SHELL_PROMPT);
                str_command_line_pos = 0;
            }
            
        }
    }
}

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
    //SystemTable->ConOut->OutputString(SystemTable->ConOut,L"Hello World!\r\n");
    StartMySystem(ImageHandle,SystemTable);
    ShellForTest(ImageHandle,SystemTable);
    return EFI_SUCCESS;
}

