/************************************************************************/
/*
*
* Filename     :  PFNC.h
* Revision     :  10.00.2564
* Content      :  This file contains definitions of the Pixel Format 
*                 Naming Convention.
*
* Copyright © Matrox Electronic Systems Ltd., 1992-2014.
* All Rights Reserved
*************************************************************************/

#ifndef _PFNC_
#define _PFNC_

// 32-bit value layout
// |31            24|23            16|15            08|07            00|
// | C| Color Layout| Effective Size |            Pixel ID             |

//===================================================
// PIXEL TYPES
//===================================================
// C
#define PFNC_CUSTOM                                0x80000000
// Color Layout
#define PFNC_MONO                                  0x01000000
#define PFNC_RGB                                   0x02000000
#define PFNC_COLOR_MASK                            0x7F000000
// Effective Size
#define PFNC_OCCUPY1BIT                            0x00010000
#define PFNC_OCCUPY2BIT                            0x00020000
#define PFNC_OCCUPY4BIT                            0x00040000
#define PFNC_OCCUPY8BIT                            0x00080000
#define PFNC_OCCUPY10BIT                           0x000A0000
#define PFNC_OCCUPY12BIT                           0x000C0000
#define PFNC_OCCUPY16BIT                           0x00100000
#define PFNC_OCCUPY24BIT                           0x00180000
#define PFNC_OCCUPY30BIT                           0x001E0000
#define PFNC_OCCUPY32BIT                           0x00200000
#define PFNC_OCCUPY36BIT                           0x00240000
#define PFNC_OCCUPY40BIT                           0x00280000
#define PFNC_OCCUPY48BIT                           0x00300000
#define PFNC_OCCUPY64BIT                           0x00400000
#define PFNC_EFFECTIVE_PIXEL_SIZE_MASK             0x00FF0000
#define PFNC_EFFECTIVE_PIXEL_SIZE_SHIFT            16

// Pixel ID
#define PFNC_ID_MASK                               0x0000FFFF

#define PFNC_BAYERBG8_ID                           (PFNC_MONO | PFNC_OCCUPY8BIT   | 0x000B)
#define PFNC_BAYERBG8_NAME                         "BayerBG8"
#define PFNC_BAYERBG10_ID                          (PFNC_MONO | PFNC_OCCUPY16BIT  | 0x000F)
#define PFNC_BAYERBG10_NAME                        "BayerBG10"
#define PFNC_BAYERBG10p_ID                         (PFNC_MONO | PFNC_OCCUPY10BIT  | 0x0052)
#define PFNC_BAYERBG10p_NAME                       "BayerBG10p"
#define PFNC_BAYERBG12_ID                          (PFNC_MONO | PFNC_OCCUPY16BIT  | 0x0013)
#define PFNC_BAYERBG12_NAME                        "BayerBG12"
#define PFNC_BAYERBG12p_ID                         (PFNC_MONO | PFNC_OCCUPY12BIT  | 0x0053)
#define PFNC_BAYERBG12p_NAME                       "BayerBG12p"
#define PFNC_BAYERBG16_ID                          (PFNC_MONO | PFNC_OCCUPY16BIT  | 0x0031)
#define PFNC_BAYERBG16_NAME                        "BayerBG16"

#define PFNC_BAYERGB8_ID                           (PFNC_MONO | PFNC_OCCUPY8BIT   | 0x000A)
#define PFNC_BAYERGB8_NAME                         "BayerGB8"
#define PFNC_BAYERGB10_ID                          (PFNC_MONO | PFNC_OCCUPY16BIT  | 0x000E)
#define PFNC_BAYERGB10_NAME                        "BayerGB10"
#define PFNC_BAYERGB10p_ID                         (PFNC_MONO | PFNC_OCCUPY10BIT  | 0x0054)
#define PFNC_BAYERGB10p_NAME                       "BayerGB10p"
#define PFNC_BAYERGB12_ID                          (PFNC_MONO | PFNC_OCCUPY16BIT  | 0x0012)
#define PFNC_BAYERGB12_NAME                        "BayerGB12"
#define PFNC_BAYERGB12p_ID                         (PFNC_MONO | PFNC_OCCUPY12BIT  | 0x0055)
#define PFNC_BAYERGB12p_NAME                       "BayerGB12p"
#define PFNC_BAYERGB16_ID                          (PFNC_MONO | PFNC_OCCUPY16BIT  | 0x0030)
#define PFNC_BAYERGB16_NAME                        "BayerGB16"

#define PFNC_BAYERGR8_ID                           (PFNC_MONO | PFNC_OCCUPY8BIT   | 0x0008)
#define PFNC_BAYERGR8_NAME                         "BayerGR8"
#define PFNC_BAYERGR10_ID                          (PFNC_MONO | PFNC_OCCUPY16BIT  | 0x000C)
#define PFNC_BAYERGR10_NAME                        "BayerGR10"
#define PFNC_BAYERGR10p_ID                         (PFNC_MONO | PFNC_OCCUPY10BIT  | 0x0056)
#define PFNC_BAYERGR10p_NAME                       "BayerGR10p"
#define PFNC_BAYERGR12_ID                          (PFNC_MONO | PFNC_OCCUPY16BIT  | 0x0010)
#define PFNC_BAYERGR12_NAME                        "BayerGR12"
#define PFNC_BAYERGR12p_ID                         (PFNC_MONO | PFNC_OCCUPY12BIT  | 0x0057)
#define PFNC_BAYERGR12p_NAME                       "BayerGR12p"
#define PFNC_BAYERGR16_ID                          (PFNC_MONO | PFNC_OCCUPY16BIT  | 0x002E)
#define PFNC_BAYERGR16_NAME                        "BayerGR16"

#define PFNC_BAYERRG8_ID                           (PFNC_MONO | PFNC_OCCUPY8BIT   | 0x0009)
#define PFNC_BAYERRG8_NAME                         "BayerRG8"
#define PFNC_BAYERRG10_ID                          (PFNC_MONO | PFNC_OCCUPY16BIT  | 0x000D)
#define PFNC_BAYERRG10_NAME                        "BayerRG10"
#define PFNC_BAYERRG10p_ID                         (PFNC_MONO | PFNC_OCCUPY10BIT  | 0x0058)
#define PFNC_BAYERRG10p_NAME                       "BayerRG10p"
#define PFNC_BAYERRG12_ID                          (PFNC_MONO | PFNC_OCCUPY16BIT  | 0x0011)
#define PFNC_BAYERRG12_NAME                        "BayerRG12"
#define PFNC_BAYERRG12p_ID                         (PFNC_MONO | PFNC_OCCUPY12BIT  | 0x0059)
#define PFNC_BAYERRG12p_NAME                       "BayerRG12p"
#define PFNC_BAYERRG16_ID                          (PFNC_MONO | PFNC_OCCUPY16BIT  | 0x002F)
#define PFNC_BAYERRG16_NAME                        "BayerRG16"

#define PFNC_BGR8_ID                               (PFNC_RGB  | PFNC_OCCUPY24BIT  | 0x0015)
#define PFNC_BGR8_NAME                             "BGR8"
#define PFNC_BGR10_ID                              (PFNC_RGB  | PFNC_OCCUPY48BIT  | 0x0019)
#define PFNC_BGR10_NAME                            "BGR10"
#define PFNC_BGR10p_ID                             (PFNC_RGB  | PFNC_OCCUPY30BIT  | 0x0048)
#define PFNC_BGR10p_NAME                           "BGR10p"
#define PFNC_BGR12_ID                              (PFNC_RGB  | PFNC_OCCUPY48BIT  | 0x001B)
#define PFNC_BGR12_NAME                            "BGR12"
#define PFNC_BGR12p_ID                             (PFNC_RGB  | PFNC_OCCUPY36BIT  | 0x0049)
#define PFNC_BGR12p_NAME                           "BGR12p"
#define PFNC_BGR14_ID                              (PFNC_RGB  | PFNC_OCCUPY48BIT  | 0x004A)
#define PFNC_BGR14_NAME                            "BGR14"
#define PFNC_BGR16_ID                              (PFNC_RGB  | PFNC_OCCUPY48BIT  | 0x004B)
#define PFNC_BGR16_NAME                            "BGR16"
#define PFNC_BGR565p_ID                            (PFNC_RGB  | PFNC_OCCUPY16BIT  | 0x0036)
#define PFNC_BGR565p_NAME                          "BGR565p"

#define PFNC_BGRa8_ID                              (PFNC_RGB  | PFNC_OCCUPY32BIT  | 0x0017)
#define PFNC_BGRa8_NAME                            "BGRa8"
#define PFNC_BGRa10_ID                             (PFNC_RGB  | PFNC_OCCUPY64BIT  | 0x004C)
#define PFNC_BGRa10_NAME                           "BGRa10"
#define PFNC_BGRa10p_ID                            (PFNC_RGB  | PFNC_OCCUPY40BIT  | 0x004D)
#define PFNC_BGRa10p_NAME                          "BGRa10p"
#define PFNC_BGRa12_ID                             (PFNC_RGB  | PFNC_OCCUPY64BIT  | 0x004E)
#define PFNC_BGRa12_NAME                           "BGRa12"
#define PFNC_BGRa12p_ID                            (PFNC_RGB  | PFNC_OCCUPY48BIT  | 0x004F)
#define PFNC_BGRa12p_NAME                          "BGRa12p"
#define PFNC_BGRa14_ID                             (PFNC_RGB  | PFNC_OCCUPY64BIT  | 0x0050)
#define PFNC_BGRa14_NAME                           "BGRa14"
#define PFNC_BGRa16_ID                             (PFNC_RGB  | PFNC_OCCUPY64BIT  | 0x0051)
#define PFNC_BGRa16_NAME                           "BGRa16"

#define PFNC_MONO1p_ID                             (PFNC_MONO | PFNC_OCCUPY1BIT   | 0x0037)
#define PFNC_MONO1p_NAME                           "Mono1p"
#define PFNC_MONO2p_ID                             (PFNC_MONO | PFNC_OCCUPY2BIT   | 0x0038)
#define PFNC_MONO2p_NAME                           "Mono2p"
#define PFNC_MONO4p_ID                             (PFNC_MONO | PFNC_OCCUPY4BIT   | 0x0039)
#define PFNC_MONO4p_NAME                           "Mono4p"
#define PFNC_MONO8_ID                              (PFNC_MONO | PFNC_OCCUPY8BIT   | 0x0001)
#define PFNC_MONO8_NAME                            "Mono8"
#define PFNC_MONO8s_ID                             (PFNC_MONO | PFNC_OCCUPY8BIT   | 0x0002)
#define PFNC_MONO8s_NAME                           "Mono8s"
#define PFNC_MONO10_ID                             (PFNC_MONO | PFNC_OCCUPY16BIT  | 0x0003)
#define PFNC_MONO10_NAME                           "Mono10"
#define PFNC_MONO10p_ID                            (PFNC_MONO | PFNC_OCCUPY10BIT  | 0x0046)
#define PFNC_MONO10p_NAME                          "Mono10p"
#define PFNC_MONO12_ID                             (PFNC_MONO | PFNC_OCCUPY16BIT  | 0x0005)
#define PFNC_MONO12_NAME                           "Mono12"
#define PFNC_MONO12p_ID                            (PFNC_MONO | PFNC_OCCUPY12BIT  | 0x0047)
#define PFNC_MONO12p_NAME                          "Mono12p"
#define PFNC_MONO14_ID                             (PFNC_MONO | PFNC_OCCUPY16BIT  | 0x0025)
#define PFNC_MONO14_NAME                           "Mono14"
#define PFNC_MONO16_ID                             (PFNC_MONO | PFNC_OCCUPY16BIT  | 0x0007)
#define PFNC_MONO16_NAME                           "Mono16"

#define PFNC_RGB8_ID                               (PFNC_RGB  | PFNC_OCCUPY24BIT  | 0x0014)
#define PFNC_RGB8_NAME                             "RGB8"
#define PFNC_RGB8_PLANAR_ID                        (PFNC_RGB  | PFNC_OCCUPY24BIT  | 0x0021)
#define PFNC_RGB8_PLANAR_NAME                      "RGB8_Planar"
#define PFNC_RGB10_ID                              (PFNC_RGB  | PFNC_OCCUPY48BIT  | 0x0018)
#define PFNC_RGB10_NAME                            "RGB10"
#define PFNC_RGB10p_ID                             (PFNC_RGB  | PFNC_OCCUPY30BIT  | 0x005C)
#define PFNC_RGB10p_NAME                           "RGB10p"
#define PFNC_RGB10p32_ID                           (PFNC_RGB  | PFNC_OCCUPY32BIT  | 0x001D)
#define PFNC_RGB10p32_NAME                         "RGB10p32"
#define PFNC_RGB10_PLANAR_ID                       (PFNC_RGB  | PFNC_OCCUPY48BIT  | 0x0022)
#define PFNC_RGB10_PLANAR_NAME                     "RGB10_Planar"
#define PFNC_RGB12_ID                              (PFNC_RGB  | PFNC_OCCUPY48BIT  | 0x001A)
#define PFNC_RGB12_NAME                            "RGB12"
#define PFNC_RGB12p_ID                             (PFNC_RGB  | PFNC_OCCUPY36BIT  | 0x005D)
#define PFNC_RGB12p_NAME                           "RGB12p"
#define PFNC_RGB12_PLANAR_ID                       (PFNC_RGB  | PFNC_OCCUPY48BIT  | 0x0023)
#define PFNC_RGB12_PLANAR_NAME                     "RGB12_Planar"
#define PFNC_RGB14_ID                              (PFNC_RGB  | PFNC_OCCUPY48BIT  | 0x005E)
#define PFNC_RGB14_NAME                            "RGB14"
#define PFNC_RGB16_ID                              (PFNC_RGB  | PFNC_OCCUPY48BIT  | 0x0033)
#define PFNC_RGB16_NAME                            "RGB16"
#define PFNC_RGB16_PLANAR_ID                       (PFNC_RGB  | PFNC_OCCUPY48BIT  | 0x0024)
#define PFNC_RGB16_PLANAR_NAME                     "RGB16_Planar"
#define PFNC_RGB565p_ID                            (PFNC_RGB  | PFNC_OCCUPY16BIT  | 0x0035)
#define PFNC_RGB565p_NAME                          "RGB565p"

#define PFNC_RGBa8_ID                              (PFNC_RGB  | PFNC_OCCUPY32BIT  | 0x0016)
#define PFNC_RGBa8_NAME                            "RGBa8"
#define PFNC_RGBa10_ID                             (PFNC_RGB  | PFNC_OCCUPY64BIT  | 0x005F)
#define PFNC_RGBa10_NAME                           "RGBa10"
#define PFNC_RGBa10p_ID                            (PFNC_RGB  | PFNC_OCCUPY40BIT  | 0x0060)
#define PFNC_RGBa10p_NAME                          "RGBa10p"
#define PFNC_RGBa12_ID                             (PFNC_RGB  | PFNC_OCCUPY64BIT  | 0x0061)
#define PFNC_RGBa12_NAME                           "RGBa12"
#define PFNC_RGBa12p_ID                            (PFNC_RGB  | PFNC_OCCUPY48BIT  | 0x0062)
#define PFNC_RGBa12p_NAME                          "RGBa12p"
#define PFNC_RGBa14_ID                             (PFNC_RGB  | PFNC_OCCUPY64BIT  | 0x0063)
#define PFNC_RGBa14_NAME                           "RGBa14"
#define PFNC_RGBa16_ID                             (PFNC_RGB  | PFNC_OCCUPY64BIT  | 0x0064)
#define PFNC_RGBa16_NAME                           "RGBa16"

#define PFNC_YCbCr411_8_ID                         (PFNC_RGB  | PFNC_OCCUPY12BIT  | 0x005A)
#define PFNC_YCbCr411_8_NAME                       "YCbCr411_8"
#define PFNC_YCbCr411_8_CbYYCrYY_ID                (PFNC_RGB  | PFNC_OCCUPY12BIT  | 0x003C)
#define PFNC_YCbCr411_8_CbYYCrYY_NAME              "YCbCr411_8_CbYYCrYY"
#define PFNC_YCbCr422_8_ID                         (PFNC_RGB  | PFNC_OCCUPY16BIT  | 0x003B)
#define PFNC_YCbCr422_8_NAME                       "YCbCr422_8"
#define PFNC_YCbCr422_8_CbYCrY_ID                  (PFNC_RGB  | PFNC_OCCUPY16BIT  | 0x0043)
#define PFNC_YCbCr422_8_CbYCrY_NAME                "YCbCr422_8_CbYCrY"
#define PFNC_YCbCr422_10_ID                        (PFNC_RGB  | PFNC_OCCUPY32BIT  | 0x0065)
#define PFNC_YCbCr422_10_NAME                      "YCbCr422_10"
#define PFNC_YCbCr422_12_ID                        (PFNC_RGB  | PFNC_OCCUPY32BIT  | 0x0066)
#define PFNC_YCbCr422_12_NAME                      "YCbCr422_12"

#define PFNC_YCbCr601_411_8_CbYYCrYY_ID            (PFNC_RGB  | PFNC_OCCUPY12BIT  | 0x003F)
#define PFNC_YCbCr601_411_8_CbYYCrYY_NAME          "YCbCr601_411_8_CbYYCrYY"
#define PFNC_YCbCr601_422_8_ID                     (PFNC_RGB  | PFNC_OCCUPY16BIT  | 0x003E)
#define PFNC_YCbCr601_422_8_NAME                   "YCbCr601_422_8"
#define PFNC_YCbCr601_422_8_CbYCrY_ID              (PFNC_RGB  | PFNC_OCCUPY16BIT  | 0x0044)
#define PFNC_YCbCr601_422_8_CbYCrY_NAME            "YCbCr601_422_8_CbYCrY"
#define PFNC_YCbCr601_8_CbYCr_ID                   (PFNC_RGB  | PFNC_OCCUPY24BIT  | 0x003D)
#define PFNC_YCbCr601_8_CbYCr_NAME                 "YCbCr601_8_CbYCr"

#define PFNC_YCbCr709_411_8_CbYYCrYY_ID            (PFNC_RGB  | PFNC_OCCUPY12BIT  | 0x0042)
#define PFNC_YCbCr709_411_8_CbYYCrYY_NAME          "YCbCr709_411_8_CbYYCrYY"
#define PFNC_YCbCr709_422_8_ID                     (PFNC_RGB  | PFNC_OCCUPY16BIT  | 0x0041)
#define PFNC_YCbCr709_422_8_NAME                   "YCbCr709_422_8"
#define PFNC_YCbCr709_422_8_CbYCrY_ID              (PFNC_RGB  | PFNC_OCCUPY16BIT  | 0x0045)
#define PFNC_YCbCr709_422_8_CbYCrY_NAME            "YCbCr709_422_8_CbYCrY"
#define PFNC_YCbCr709_8_CbYCr_ID                   (PFNC_RGB  | PFNC_OCCUPY24BIT  | 0x0040)
#define PFNC_YCbCr709_8_CbYCr_NAME                 "YCbCr709_8_CbYCr"

#define PFNC_YCbCr8_ID                             (PFNC_RGB  | PFNC_OCCUPY24BIT  | 0x005B)
#define PFNC_YCbCr8_NAME                           "YCbCr8"
#define PFNC_YCbCr8_CbYCr_ID                       (PFNC_RGB  | PFNC_OCCUPY24BIT  | 0x003A)
#define PFNC_YCbCr8_CbYCr_NAME                     "YCbCr8_CbYCr"

#define PFNC_YUV411_8_UYYVYY_ID                    (PFNC_RGB  | PFNC_OCCUPY12BIT  | 0x001E)
#define PFNC_YUV411_8_UYYVYY_NAME                  "YUV411_8_UYYVYY"
#define PFNC_YUV422_8_ID                           (PFNC_RGB  | PFNC_OCCUPY16BIT  | 0x0032)
#define PFNC_YUV422_8_NAME                         "YUV422_8"
#define PFNC_YUV422_8_UYVY_ID                      (PFNC_RGB  | PFNC_OCCUPY16BIT  | 0x001F)
#define PFNC_YUV422_8_UYVY_NAME                    "YUV422_8_UYVY"
#define PFNC_YUV8_UYV_ID                           (PFNC_RGB  | PFNC_OCCUPY24BIT  | 0x0020)
#define PFNC_YUV8_UYV_NAME                         "YUV8_UYV"

// GigEVision Specific
#define GEV_MONO10_PACKED_ID                       (PFNC_MONO | PFNC_OCCUPY12BIT  | 0x0004)
#define GEV_MONO10_PACKED_NAME                     "Mono10Packed"
#define GEV_MONO12_PACKED_ID                       (PFNC_MONO | PFNC_OCCUPY12BIT  | 0x0006)
#define GEV_MONO12_PACKED_NAME                     "Mono12Packed"
#define GEV_BAYGR10_PACKED_ID                      (PFNC_MONO | PFNC_OCCUPY12BIT  | 0x0026)
#define GEV_BAYGR10_PACKED_NAME                    "BayerGR10Packed"
#define GEV_BAYRG10_PACKED_ID                      (PFNC_MONO | PFNC_OCCUPY12BIT  | 0x0027)
#define GEV_BAYRG10_PACKED_NAME                    "BayerRG10Packed"
#define GEV_BAYGB10_PACKED_ID                      (PFNC_MONO | PFNC_OCCUPY12BIT  | 0x0028)
#define GEV_BAYGB10_PACKED_NAME                    "BayerGB10Packed"
#define GEV_BAYBG10_PACKED_ID                      (PFNC_MONO | PFNC_OCCUPY12BIT  | 0x0029)
#define GEV_BAYBG10_PACKED_NAME                    "BayerBG10Packed"
#define GEV_BAYGR12_PACKED_ID                      (PFNC_MONO | PFNC_OCCUPY12BIT  | 0x002A)
#define GEV_BAYGR12_PACKED_NAME                    "BayerGR12Packed"
#define GEV_BAYRG12_PACKED_ID                      (PFNC_MONO | PFNC_OCCUPY12BIT  | 0x002B)
#define GEV_BAYRG12_PACKED_NAME                    "BayerRG12Packed"
#define GEV_BAYGB12_PACKED_ID                      (PFNC_MONO | PFNC_OCCUPY12BIT  | 0x002C)
#define GEV_BAYGB12_PACKED_NAME                    "BayerGB12Packed"
#define GEV_BAYBG12_PACKED_ID                      (PFNC_MONO | PFNC_OCCUPY12BIT  | 0x002D)
#define GEV_BAYBG12_PACKED_NAME                    "BayerBG12Packed"
#define GEV_RGB10V1_PACKED_ID                      (PFNC_RGB  | PFNC_OCCUPY32BIT  | 0x001C)
#define GEV_RGB12V1_PACKED_ID                      (PFNC_RGB  | PFNC_OCCUPY32BIT  | 0x0034)
// End GigEVision Specific

// 16-bit value layout
// |15            08|07    04|03    00|
// |    Data Type   | Subtype| Wdith  |

// Data Type
#define PFNC16_RAW                                 0x0000
#define PFNC16_MONO                                0x0100
#define PFNC16_PLANAR                              0x0200
#define PFNC16_BAYER                               0x0300
#define PFNC16_RGB                                 0x0400
#define PFNC16_RGBa                                0x0500
#define PFNC16_YUV                                 0x0600
#define PFNC16_YCbCr601                            0x0700
#define PFNC16_YCbCr709                            0x0800
#define PFNC16_TYPE_MASK                           0xFF00
// Subtype
#define PFNC16_PLANE1                              0x0010
#define PFNC16_PLANE2                              0x0020
#define PFNC16_PLANE3                              0x0030
#define PFNC16_PLANE4                              0x0040
#define PFNC16_PLANE5                              0x0050
#define PFNC16_PLANE6                              0x0060
#define PFNC16_PLANE7                              0x0070
#define PFNC16_PLANE8                              0x0080
#define PFNC16_PLANE9                              0x0090
#define PFNC16_PLANE10                             0x00A0
#define PFNC16_PLANE11                             0x00B0
#define PFNC16_PLANE12                             0x00C0
#define PFNC16_PLANE13                             0x00D0
#define PFNC16_PLANE14                             0x00E0
#define PFNC16_PLANE15                             0x00F0
#define PFNC16_BAYERGR                             0x0010
#define PFNC16_BAYERRG                             0x0020
#define PFNC16_BAYERGB                             0x0030
#define PFNC16_BAYERBG                             0x0040
#define PFNC16_411                                 0x0010
#define PFNC16_422                                 0x0020
#define PFNC16_444                                 0x0030
#define PFNC16_STYPE_MASK                          0x00F0
// Width
#define PFNC16_8_BITS                              0x0001
#define PFNC16_10_BITS                             0x0002
#define PFNC16_12_BITS                             0x0003
#define PFNC16_14_BITS                             0x0004
#define PFNC16_16_BITS                             0x0005
#define PFNC16_WIDTH_MASK                          0x000F

#define PFNC_BAYERBG8_ID16                         (PFNC16_BAYER     | PFNC16_BAYERBG  | PFNC16_8_BITS)
#define PFNC_BAYERBG8_NAME                         "BayerBG8"
#define PFNC_BAYERBG10_PMSB_ID16                   (PFNC16_BAYER     | PFNC16_BAYERBG  | PFNC16_10_BITS)
#define PFNC_BAYERBG10_PMSB_NAME                   "BayerBG10pmsb"
#define PFNC_BAYERBG12_PMSB_ID16                   (PFNC16_BAYER     | PFNC16_BAYERBG  | PFNC16_12_BITS)
#define PFNC_BAYERBG12_PMSB_NAME                   "BayerBG12pmsb"
#define PFNC_BAYERBG14_PMSB_ID16                   (PFNC16_BAYER     | PFNC16_BAYERBG  | PFNC16_14_BITS)
#define PFNC_BAYERBG14_PMSB_NAME                   "BayerBG14pmsb"
#define PFNC_BAYERBG16_ID16                        (PFNC16_BAYER     | PFNC16_BAYERBG  | PFNC16_16_BITS)
#define PFNC_BAYERBG16_NAME                        "BayerBG16"

#define PFNC_BAYERGB8_ID16                         (PFNC16_BAYER     | PFNC16_BAYERGB  | PFNC16_8_BITS)
#define PFNC_BAYERGB8_NAME                         "BayerGB8"
#define PFNC_BAYERGB10_PMSB_ID16                   (PFNC16_BAYER     | PFNC16_BAYERGB  | PFNC16_10_BITS)
#define PFNC_BAYERGB10_PMSB_NAME                   "BayerGB10pmsb"
#define PFNC_BAYERGB12_PMSB_ID16                   (PFNC16_BAYER     | PFNC16_BAYERGB  | PFNC16_12_BITS)
#define PFNC_BAYERGB12_PMSB_NAME                   "BayerGB12pmsb"
#define PFNC_BAYERGB14_PMSB_ID16                   (PFNC16_BAYER     | PFNC16_BAYERGB  | PFNC16_14_BITS)
#define PFNC_BAYERGB14_PMSB_NAME                   "BayerGB14pmsb"
#define PFNC_BAYERGB16_ID16                        (PFNC16_BAYER     | PFNC16_BAYERGB  | PFNC16_16_BITS)
#define PFNC_BAYERGB16_NAME                        "BayerGB16"

#define PFNC_BAYERGR8_ID16                         (PFNC16_BAYER     | PFNC16_BAYERGR  | PFNC16_8_BITS)
#define PFNC_BAYERGR8_NAME                         "BayerGR8"
#define PFNC_BAYERGR10_PMSB_ID16                   (PFNC16_BAYER     | PFNC16_BAYERGR  | PFNC16_10_BITS)
#define PFNC_BAYERGR10_PMSB_NAME                   "BayerGR10pmsb"
#define PFNC_BAYERGR12_PMSB_ID16                   (PFNC16_BAYER     | PFNC16_BAYERGR  | PFNC16_12_BITS)
#define PFNC_BAYERGR12_PMSB_NAME                   "BayerGR12pmsb"
#define PFNC_BAYERGR14_PMSB_ID16                   (PFNC16_BAYER     | PFNC16_BAYERGR  | PFNC16_14_BITS)
#define PFNC_BAYERGR14_PMSB_NAME                   "BayerGR14pmsb"
#define PFNC_BAYERGR16_ID16                        (PFNC16_BAYER     | PFNC16_BAYERGR  | PFNC16_16_BITS)
#define PFNC_BAYERGR16_NAME                        "BayerGR16"

#define PFNC_BAYERRG8_ID16                         (PFNC16_BAYER     | PFNC16_BAYERRG  | PFNC16_8_BITS)
#define PFNC_BAYERRG8_NAME                         "BayerRG8"
#define PFNC_BAYERRG10_PMSB_ID16                   (PFNC16_BAYER     | PFNC16_BAYERRG  | PFNC16_10_BITS)
#define PFNC_BAYERRG10_PMSB_NAME                   "BayerRG10pmsb"
#define PFNC_BAYERRG12_PMSB_ID16                   (PFNC16_BAYER     | PFNC16_BAYERRG  | PFNC16_12_BITS)
#define PFNC_BAYERRG12_PMSB_NAME                   "BayerRG12pmsb"
#define PFNC_BAYERRG14_PMSB_ID16                   (PFNC16_BAYER     | PFNC16_BAYERRG  | PFNC16_14_BITS)
#define PFNC_BAYERRG14_PMSB_NAME                   "BayerRG14pmsb"
#define PFNC_BAYERRG16_ID16                        (PFNC16_BAYER     | PFNC16_BAYERRG  | PFNC16_16_BITS)
#define PFNC_BAYERRG16_NAME                        "BayerRG16"

#define PFNC_MONO8_ID16                            (PFNC16_MONO                        | PFNC16_8_BITS)
#define PFNC_MONO8_NAME                            "Mono8"
#define PFNC_MONO10_PMSB_ID16                      (PFNC16_MONO                        | PFNC16_10_BITS)
#define PFNC_MONO10_PMSB_NAME                      "Mono10pmsb"
#define PFNC_MONO12_PMSB_ID16                      (PFNC16_MONO                        | PFNC16_12_BITS)
#define PFNC_MONO12_PMSB_NAME                      "Mono12pmsb"
#define PFNC_MONO14_PMSB_ID16                      (PFNC16_MONO                        | PFNC16_14_BITS)
#define PFNC_MONO14_PMSB_NAME                      "Mono14pmsb"
#define PFNC_MONO16_ID16                           (PFNC16_MONO                        | PFNC16_16_BITS)
#define PFNC_MONO16_NAME                           "Mono16"

#define PFNC_RGB8_ID16                             (PFNC16_RGB                         | PFNC16_8_BITS)
#define PFNC_RGB8_NAME                             "RGB8"
#define PFNC_RGB10_PMSB_ID16                       (PFNC16_RGB                         | PFNC16_10_BITS)
#define PFNC_RGB10_PMSB_NAME                       "RGB10pmsb"
#define PFNC_RGB12_PMSB_ID16                       (PFNC16_RGB                         | PFNC16_12_BITS)
#define PFNC_RGB12_PMSB_NAME                       "RGB12pmsb"
#define PFNC_RGB14_PMSB_ID16                       (PFNC16_RGB                         | PFNC16_14_BITS)
#define PFNC_RGB14_PMSB_NAME                       "RGB14pmsb"
#define PFNC_RGB16_ID16                            (PFNC16_RGB                         | PFNC16_16_BITS)
#define PFNC_RGB16_NAME                            "RGB16"

#define PFNC_RGBa8_ID16                            (PFNC16_RGBa                        | PFNC16_8_BITS)
#define PFNC_RGBa8_NAME                            "RGBa8"
#define PFNC_RGBa10_PMSB_ID16                      (PFNC16_RGBa                        | PFNC16_10_BITS)
#define PFNC_RGBa10_PMSB_NAME                      "RGBa10pmsb"
#define PFNC_RGBa12_PMSB_ID16                      (PFNC16_RGBa                        | PFNC16_12_BITS)
#define PFNC_RGBa12_PMSB_NAME                      "RGBa12pmsb"
#define PFNC_RGBa14_PMSB_ID16                      (PFNC16_RGBa                        | PFNC16_14_BITS)
#define PFNC_RGBa14_PMSB_NAME                      "RGBa14pmsb"
#define PFNC_RGBa16_ID16                           (PFNC16_RGBa                        | PFNC16_16_BITS)
#define PFNC_RGBa16_NAME                           "RGBa16"

#define PFNC_YCbCr601_411_8_ID16                   (PFNC16_YCbCr601  | PFNC16_411      | PFNC16_8_BITS)
#define PFNC_YCbCr601_411_8_NAME                   "YCbCr601_411_8"
#define PFNC_YCbCr601_411_10_PMSB_ID16             (PFNC16_YCbCr601  | PFNC16_411      | PFNC16_10_BITS)
#define PFNC_YCbCr601_411_10_PMSB_NAME             "YCbCr601_411_10pmsb"
#define PFNC_YCbCr601_411_12_PMSB_ID16             (PFNC16_YCbCr601  | PFNC16_411      | PFNC16_12_BITS)
#define PFNC_YCbCr601_411_12_PMSB_NAME             "YCbCr601_411_12pmsb"
#define PFNC_YCbCr601_411_14_PMSB_ID16             (PFNC16_YCbCr601  | PFNC16_411      | PFNC16_14_BITS)
#define PFNC_YCbCr601_411_14_PMSB_NAME             "YCbCr601_411_14pmsb"
#define PFNC_YCbCr601_411_16_ID16                  (PFNC16_YCbCr601  | PFNC16_411      | PFNC16_16_BITS)
#define PFNC_YCbCr601_411_16_NAME                  "YCbCr601_411_16"

#define PFNC_YCbCr601_422_8_ID16                   (PFNC16_YCbCr601  | PFNC16_422      | PFNC16_8_BITS)
#define PFNC_YCbCr601_422_8_NAME                   "YCbCr601_422_8"
#define PFNC_YCbCr601_422_10_PMSB_ID16             (PFNC16_YCbCr601  | PFNC16_422      | PFNC16_10_BITS)
#define PFNC_YCbCr601_422_10_PMSB_NAME             "YCbCr601_422_10pmsb"
#define PFNC_YCbCr601_422_12_PMSB_ID16             (PFNC16_YCbCr601  | PFNC16_422      | PFNC16_12_BITS)
#define PFNC_YCbCr601_422_12_PMSB_NAME             "YCbCr601_422_12pmsb"
#define PFNC_YCbCr601_422_14_PMSB_ID16             (PFNC16_YCbCr601  | PFNC16_422      | PFNC16_14_BITS)
#define PFNC_YCbCr601_422_14_PMSB_NAME             "YCbCr601_422_14pmsb"
#define PFNC_YCbCr601_422_16_ID16                  (PFNC16_YCbCr601  | PFNC16_422      | PFNC16_16_BITS)
#define PFNC_YCbCr601_422_16_NAME                  "YCbCr601_422_16"

#define PFNC_YCbCr601_8_ID16                       (PFNC16_YCbCr601  | PFNC16_444      | PFNC16_8_BITS)
#define PFNC_YCbCr601_8_NAME                       "YCbCr601_8"
#define PFNC_YCbCr601_10_PMSB_ID16                 (PFNC16_YCbCr601  | PFNC16_444      | PFNC16_10_BITS)
#define PFNC_YCbCr601_10_PMSB_NAME                 "YCbCr601_10pmsb"
#define PFNC_YCbCr601_12_PMSB_ID16                 (PFNC16_YCbCr601  | PFNC16_444      | PFNC16_12_BITS)
#define PFNC_YCbCr601_12_PMSB_NAME                 "YCbCr601_12pmsb"
#define PFNC_YCbCr601_14_PMSB_ID16                 (PFNC16_YCbCr601  | PFNC16_444      | PFNC16_14_BITS)
#define PFNC_YCbCr601_14_PMSB_NAME                 "YCbCr601_14pmsb"
#define PFNC_YCbCr601_16_ID16                      (PFNC16_YCbCr601  | PFNC16_444      | PFNC16_16_BITS)
#define PFNC_YCbCr601_16_NAME                      "YCbCr601_16"

#define PFNC_YCbCr709_411_8_ID16                   (PFNC16_YCbCr709  | PFNC16_411      | PFNC16_8_BITS)
#define PFNC_YCbCr709_411_8_NAME                   "YCbCr709_411_8"
#define PFNC_YCbCr709_411_10_PMSB_ID16             (PFNC16_YCbCr709  | PFNC16_411      | PFNC16_10_BITS)
#define PFNC_YCbCr709_411_10_PMSB_NAME             "YCbCr709_411_10pmsb"
#define PFNC_YCbCr709_411_12_PMSB_ID16             (PFNC16_YCbCr709  | PFNC16_411      | PFNC16_12_BITS)
#define PFNC_YCbCr709_411_12_PMSB_NAME             "YCbCr709_411_12pmsb"
#define PFNC_YCbCr709_411_14_PMSB_ID16             (PFNC16_YCbCr709  | PFNC16_411      | PFNC16_14_BITS)
#define PFNC_YCbCr709_411_14_PMSB_NAME             "YCbCr709_411_14pmsb"
#define PFNC_YCbCr709_411_16_ID16                  (PFNC16_YCbCr709  | PFNC16_411      | PFNC16_16_BITS)
#define PFNC_YCbCr709_411_16_NAME                  "YCbCr709_411_16"

#define PFNC_YCbCr709_422_8_ID16                   (PFNC16_YCbCr709  | PFNC16_422      | PFNC16_8_BITS)
#define PFNC_YCbCr709_422_8_NAME                   "YCbCr709_422_8"
#define PFNC_YCbCr709_422_10_PMSB_ID16             (PFNC16_YCbCr709  | PFNC16_422      | PFNC16_10_BITS)
#define PFNC_YCbCr709_422_10_PMSB_NAME             "YCbCr709_422_10pmsb"
#define PFNC_YCbCr709_422_12_PMSB_ID16             (PFNC16_YCbCr709  | PFNC16_422      | PFNC16_12_BITS)
#define PFNC_YCbCr709_422_12_PMSB_NAME             "YCbCr709_422_12pmsb"
#define PFNC_YCbCr709_422_14_PMSB_ID16             (PFNC16_YCbCr709  | PFNC16_422      | PFNC16_14_BITS)
#define PFNC_YCbCr709_422_14_PMSB_NAME             "YCbCr709_422_14pmsb"
#define PFNC_YCbCr709_422_16_ID16                  (PFNC16_YCbCr709  | PFNC16_422      | PFNC16_16_BITS)
#define PFNC_YCbCr709_422_16_NAME                  "YCbCr709_422_16"

#define PFNC_YCbCr709_8_ID16                       (PFNC16_YCbCr709  | PFNC16_444      | PFNC16_8_BITS)
#define PFNC_YCbCr709_8_NAME                       "YCbCr709_8"
#define PFNC_YCbCr709_10_PMSB_ID16                 (PFNC16_YCbCr709  | PFNC16_444      | PFNC16_10_BITS)
#define PFNC_YCbCr709_10_PMSB_NAME                 "YCbCr709_10pmsb"
#define PFNC_YCbCr709_12_PMSB_ID16                 (PFNC16_YCbCr709  | PFNC16_444      | PFNC16_12_BITS)
#define PFNC_YCbCr709_12_PMSB_NAME                 "YCbCr709_12pmsb"
#define PFNC_YCbCr709_14_PMSB_ID16                 (PFNC16_YCbCr709  | PFNC16_444      | PFNC16_14_BITS)
#define PFNC_YCbCr709_14_PMSB_NAME                 "YCbCr709_14pmsb"
#define PFNC_YCbCr709_16_ID16                      (PFNC16_YCbCr709  | PFNC16_444      | PFNC16_16_BITS)
#define PFNC_YCbCr709_16_NAME                      "YCbCr709_16"

#define PFNC_YUV411_8_ID16                         (PFNC16_YUV       | PFNC16_411      | PFNC16_8_BITS)
#define PFNC_YUV411_8_NAME                         "YUV411_8"
#define PFNC_YUV411_10_PMSB_ID16                   (PFNC16_YUV       | PFNC16_411      | PFNC16_10_BITS)
#define PFNC_YUV411_10_PMSB_NAME                   "YUV411_10pmsb"
#define PFNC_YUV411_12_PMSB_ID16                   (PFNC16_YUV       | PFNC16_411      | PFNC16_12_BITS)
#define PFNC_YUV411_12_PMSB_NAME                   "YUV411_12pmsb"
#define PFNC_YUV411_14_PMSB_ID16                   (PFNC16_YUV       | PFNC16_411      | PFNC16_14_BITS)
#define PFNC_YUV411_14_PMSB_NAME                   "YUV411_14pmsb"
#define PFNC_YUV411_16_ID16                        (PFNC16_YUV       | PFNC16_411      | PFNC16_16_BITS)
#define PFNC_YUV411_16_NAME                        "YUV411_16"

#define PFNC_YUV422_8_ID16                         (PFNC16_YUV       | PFNC16_422      | PFNC16_8_BITS)
#define PFNC_YUV422_8_NAME                         "YUV422_8"
#define PFNC_YUV422_10_PMSB_ID16                   (PFNC16_YUV       | PFNC16_422      | PFNC16_10_BITS)
#define PFNC_YUV422_10_PMSB_NAME                   "YUV422_10pmsb"
#define PFNC_YUV422_12_PMSB_ID16                   (PFNC16_YUV       | PFNC16_422      | PFNC16_12_BITS)
#define PFNC_YUV422_12_PMSB_NAME                   "YUV422_12pmsb"
#define PFNC_YUV422_14_PMSB_ID16                   (PFNC16_YUV       | PFNC16_422      | PFNC16_14_BITS)
#define PFNC_YUV422_14_PMSB_NAME                   "YUV422_14pmsb"
#define PFNC_YUV422_16_ID16                        (PFNC16_YUV       | PFNC16_422      | PFNC16_16_BITS)
#define PFNC_YUV422_16_NAME                        "YUV422_16"

#define PFNC_YUV_8_ID16                            (PFNC16_YUV       | PFNC16_444      | PFNC16_8_BITS)
#define PFNC_YUV_8_NAME                            "YUV8"
#define PFNC_YUV_10_PMSB_ID16                      (PFNC16_YUV       | PFNC16_444      | PFNC16_10_BITS)
#define PFNC_YUV_10_PMSB_NAME                      "YUV10pmsb"
#define PFNC_YUV_12_PMSB_ID16                      (PFNC16_YUV       | PFNC16_444      | PFNC16_12_BITS)
#define PFNC_YUV_12_PMSB_NAME                      "YUV12pmsb"
#define PFNC_YUV_14_PMSB_ID16                      (PFNC16_YUV       | PFNC16_444      | PFNC16_14_BITS)
#define PFNC_YUV_14_PMSB_NAME                      "YUV14pmsb"
#define PFNC_YUV_16_ID16                           (PFNC16_YUV       | PFNC16_444      | PFNC16_16_BITS)
#define PFNC_YUV_16_NAME                           "YUV16"

#endif