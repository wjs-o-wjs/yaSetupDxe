## @file
#  This package contains build scripts for building YaSetupPkg, A UEFI Settings utility.
#
#  wjs+o(wjs) team, 2022, All rights granted.
#
#  SPDX-License-Identifier: DO WHAT THE F**K YOU WANT TO PUBLIC LICENSE.
#
##

[Defines]
  PLATFORM_NAME                  = YaSetupPkg
  PLATFORM_GUID                  = 46FE4939-3A5E-40A0-B1B4-4A1E3D7C282A
  PLATFORM_VERSION               = 0.2
  DSC_SPECIFICATION              = 0x00010005
  SUPPORTED_ARCHITECTURES        = X64
  OUTPUT_DIRECTORY               = Build/YaSetupPkg
  BUILD_TARGETS                  = DEBUG|RELEASE|NOOPT
  SKUID_IDENTIFIER               = DEFAULT

DEFINE BUILD_FOR_EMULATOR_PKG = TRUE

!ifdef BUILD_FOR_EMULATOR_PKG
[BuildOptions]
  GCC:RELEASE_*_*_CC_FLAGS             = -DMDEPKG_NDEBUG -DBUILD_FOR_EMULATOR_PKG
  GCC:*_*_*_CC_FLAGS                   = -DBUILD_FOR_EMULATOR_PKG
!else
[BuildOptions]
  GCC:RELEASE_*_*_CC_FLAGS             = -DMDEPKG_NDEBUG
  GCC:*_*_*_CC_FLAGS                   =
!endif

[LibraryClasses]
  #
  # Entry Point Libraries
  #
  UefiApplicationEntryPoint|MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf
  #
  # Common Libraries
  #
  BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
  BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
  UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
  UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf
  UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
  DevicePathLib|MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf
  MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
  HobLib|MdePkg/Library/DxeHobLib/DxeHobLib.inf

  # Added for the EmulatorPkg.
!ifdef BUILD_FOR_EMULATOR_PKG
  EmuThunkLib|EmulatorPkg/Library/DxeEmuLib/DxeEmuLib.inf
  DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf
!else
  DebugLib|MdePkg/Library/UefiDebugLibStdErr/UefiDebugLibStdErr.inf
  DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf
!endif
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  RegisterFilterLib|MdePkg/Library/RegisterFilterLibNull/RegisterFilterLibNull.inf
  #
  # Our own Libraries
  #
  ComposerLib|YaSetupPkg/Library/GopComposerLib/GopComposerLib.inf
  MouseLib|YaSetupPkg/Library/EmulatedMouseLib/EmulatedMouseLib.inf
  KeyboardLib|YaSetupPkg/Library/KeyboardLib/KeyboardLib.inf
  CommonWidgetLib|YaSetupPkg/Library/CommonWidgetLib/CommonWidgetLib.inf
  MainMessageLooperLib|YaSetupPkg/Library/MainMessageLooperLib/MainMessageLooperLib.inf
[Components]
  YaSetupPkg/Presenter/Presenter.inf {
    <LibraryClasses>
    DebugLib|MdePkg/Library/BaseDebugLibSerialPort/BaseDebugLibSerialPort.inf
    SerialPortLib|EmulatorPkg/Library/DxeEmuStdErrSerialPortLib/DxeEmuStdErrSerialPortLib.inf
  }
[PcdsFixedAtBuild]
  gYaSetupPkgTokenSpaceGuid.SetupWindowTitle|L"BIOS Setup Utility - ECGM Demo Board"
  gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0x80000040
# Theme
!include Theme/DefaultTheme.inc.dsc
