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

[BuildOptions]
  GCC:RELEASE_*_*_CC_FLAGS             = -DMDEPKG_NDEBUG
  GCC:*_*_*_CC_FLAGS                   =
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
  DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
  DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  RegisterFilterLib|MdePkg/Library/RegisterFilterLibNull/RegisterFilterLibNull.inf
  #
  # Our own Libraries
  #
  ComposerLib|YaSetupPkg/Library/GopComposerLib/GopComposerLib.inf
  MouseLib|YaSetupPkg/Library/EmulatedMouseLib/EmulatedMouseLib.inf
  CommonWidgetLib|YaSetupPkg/Library/CommonWidgetLib/CommonWidgetLib.inf
[Components]
  YaSetupPkg/Presenter/Presenter.inf
[PcdsFixedAtBuild]
  gYaSetupPkgTokenSpaceGuid.SetupWindowTitle|L"BIOS Setup Utility - ECGM Demo Board"
# Theme
!include Theme/DefaultTheme.inc.dsc
