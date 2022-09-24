#include <Presenter/Entry.h>
#include <Protocol/SimpleTextIn.h>
#include <Library/UefiMouseLib/UefiMouseLib.h>
#include <Library/UefiKeyboardLib/UefiKeyboardLib.h>
#include <Library/UefiMouseLib/UefiMouseLib.h>
#include <Library/UefiAsyncTimerLib/UefiAsyncTimerLib.h>
#include <Library/UefiBasicPainterLib/UefiBasicPainterLib.h>
#define SHELL_PROMPT L"Baby Shell> "
#define STR_COMMAND_LINE_SIZE 1024

void test_func(char * buffer){
    Print(L"!!!!!!!!%s\r\n\0",buffer);
}
void StartMySystem(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable){
    KeyboardService * ks = CreateKeyboardService(SystemTable);
    EFI_KEY_DATA key_data = {{0, L'q'}, {0, 0}};
    void * test;
    ks->BindKey(ks,&key_data,test_func,&test);

    BasicPainterService * bps = CreateBasicPainterService(SystemTable);
    bps->InitGraphicsOutputProtocol(bps);
    bps->SetColor(bps,0xff,0xff,0xff,0x80)
       ->SetStartPointer(bps,100,100)
       ->Draw(bps,BasicPointerDrawTypePixel);


    /*

    MouseService * ms = CreateMouseService(SystemTable);
    if (ms == NULL){
        Print(L"CreateMouseService Err\n");
    }
    ms->InitSimplePointerProtocol(ms);
    unsigned long long status;
    EFI_SIMPLE_POINTER_STATE s;
    unsigned long long waitidx;

    ms->SPP->Reset(ms->SPP, FALSE);

    while (1) {
        ms->SystemTable->BootServices->WaitForEvent(1, &(ms->SPP->WaitForInput),
                           &waitidx);
        status = ms->SPP->GetState(ms->SPP, &s);
        if (!status) {
            
            Print(L"%p\n",s.RelativeMovementX);
            Print(L" ");
            Print(L"%p\n",s.RelativeMovementY);
            Print(L" ");
            Print(L"%p\n",s.RelativeMovementZ);
            Print(L" ");
            Print(L"%p\n",s.LeftButton);
            Print(L" ");
            Print(L"%p\n",s.RightButton);
            Print(L"\r\n");
        }
    }

    if (EFI_ERROR(status)){
        Print(L"Mouse Err\n");
    }
    ms->SPP->Reset(ms->SPP, FALSE);

    if (EFI_ERROR(status)){
        Print(L"Mouse Err\n");
    }else{
        Print(L"Mouse Success\n");
        ms->StartTimer(ms);
    }*/

    
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
    //ShellForTest(ImageHandle,SystemTable);
    while (1);
    return EFI_SUCCESS;
}

