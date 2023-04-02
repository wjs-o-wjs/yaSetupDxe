## @file
#  This package defines a default theme for YaSetupPkg, A UEFI Settings utility.
#
#  wjs+o(wjs) team, 2023, All rights granted.
#
#  SPDX-License-Identifier: DO WHAT THE F**K YOU WANT TO PUBLIC LICENSE.
#
##

[PcdsFixedAtBuild]
  gYaSetupPkgTokenSpaceGuid.BackgroudColor      | 0xFFEFF0F1
  gYaSetupPkgTokenSpaceGuid.WindowCaptionColor  | 0xFFDEE0E2
  gYaSetupPkgTokenSpaceGuid.WindowCaptionHeight | 36
  gYaSetupPkgTokenSpaceGuid.DesiredScaleTargetW | 1920
  gYaSetupPkgTokenSpaceGuid.DesiredScaleTargetH | 1080
  gYaSetupPkgTokenSpaceGuid.CursorImageWidth    | 20
  gYaSetupPkgTokenSpaceGuid.CursorImageHeight   | 31
  gYaSetupPkgTokenSpaceGuid.PrimaryTextColor    | 0x002d2926
  gYaSetupPkgTokenSpaceGuid.BorderColor         | 0xFFDADCDE

  # The UEFI Spec says one must set the variable in a single line. So this could be SO LONG......
  gYaSetupPkgTokenSpaceGuid.CursorImage         | {0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xe5,0xa3,0x1e,0xfb,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xe7,0xab,0x24,0xee,0xe4,0xa2,0x1d,0xfc,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xee,0xbb,0x30,0xdc,0xe2,0x9b,0x19,0xff,0xe4,0xa2,0x1d,0xfc,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xe5,0xa6,0x20,0xf7,0xe2,0x9b,0x19,0xff,0xe4,0xa1,0x1c,0xfc,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xec,0xb8,0x2b,0xda,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe4,0xa1,0x1c,0xfc,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf2,0xc1,0x36,0xf8,0xe4,0xa0,0x1c,0xfd,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe4,0xa1,0x1c,0xfc,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xea,0xb4,0x27,0xdf,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe4,0xa1,0x1c,0xfc,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xef,0xbe,0x33,0xed,0xe3,0x9d,0x1a,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe4,0xa1,0x1b,0xfc,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xe9,0xae,0x22,0xe9,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe4,0xa1,0x1b,0xfc,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xef,0xbd,0x2f,0xdf,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe4,0xa1,0x1b,0xfc,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xe7,0xa8,0x1d,0xf4,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe4,0xa1,0x1a,0xfc,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xed,0xba,0x28,0xd9,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe4,0xa1,0x1a,0xfc,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc2,0x34,0xfc,0xe6,0xa3,0x1b,0xfb,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe4,0xa1,0x1a,0xfc,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xeb,0xb3,0x23,0xdd,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe4,0xa1,0x1a,0xfc,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x34,0xf1,0xe3,0x9f,0x1a,0xfe,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe4,0xa1,0x19,0xfc,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xea,0xaf,0x1f,0xe5,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe4,0xa1,0x19,0xfc,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xef,0xbd,0x2d,0xe4,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe5,0xa2,0x19,0xfb,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xe8,0xa9,0x1c,0xf0,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0xe5,0xa2,0x19,0xfb,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xed,0xbb,0x25,0xda,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xfe,0xe6,0xa3,0x1a,0xfa,0xe2,0x9b,0x19,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xfe,0xf1,0xc1,0x35,0xfb,0xf1,0xc1,0x35,0xff,0xec,0xb6,0x1e,0xdb,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf3,0xc1,0x33,0xf5,0xe3,0x9f,0x18,0xfe,0xe2,0x9b,0x19,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xea,0xb0,0x1b,0xe2,0xe2,0x9b,0x19,0xff,0xe3,0x9d,0x18,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf0,0xbd,0x2d,0xe8,0xe2,0x9c,0x19,0xff,0xe2,0x9b,0x19,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xe8,0xab,0x18,0xec,0xe2,0x9b,0x19,0xff,0xe4,0xa0,0x18,0xfd,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0xff,0xff,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xf1,0xc2,0x36,0xe0,0xf1,0xc1,0x35,0xff,0xef,0xbc,0x26,0xdc,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf1,0xc1,0x35,0xff,0xe6,0xa6,0x17,0xf6,0xe2,0x9b,0x19,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xf1,0xc1,0x36,0xf3,0xf1,0xc1,0x35,0xff,0xed,0xb7,0x1d,0xd9,0xe2,0x9b,0x19,0xff,0xe2,0x9b,0x19,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0xf1,0xc1,0x35,0xff,0xf0,0xc2,0x34,0xfa,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
