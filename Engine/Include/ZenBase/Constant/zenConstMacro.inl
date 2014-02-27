//=================================================================================================
//! Macro pre-processor repeating expression (support 1 to 100)
//! _PREFIX_ and _SUFFIX_ parameter are macro in the form :
//! #define EXPRESSION(N)
//! where N is the current expansion number.
//=================================================================================================

//! @cond DOXYGEN_IGNORE
#define ZENRepeat_0(_PREFIX, _SUFFIX)
#define ZENRepeat_1(_PREFIX, _SUFFIX)	_PREFIX(1)_SUFFIX(1)
#define ZENRepeat_2(_PREFIX, _SUFFIX)	_PREFIX(2)ZENRepeat_1(_PREFIX, _SUFFIX)_SUFFIX(2)
#define ZENRepeat_3(_PREFIX, _SUFFIX)	_PREFIX(3)ZENRepeat_2(_PREFIX, _SUFFIX)_SUFFIX(3)
#define ZENRepeat_4(_PREFIX, _SUFFIX)	_PREFIX(4)ZENRepeat_3(_PREFIX, _SUFFIX)_SUFFIX(4)
#define ZENRepeat_5(_PREFIX, _SUFFIX)	_PREFIX(5)ZENRepeat_4(_PREFIX, _SUFFIX)_SUFFIX(5)
#define ZENRepeat_6(_PREFIX, _SUFFIX)	_PREFIX(6)ZENRepeat_5(_PREFIX, _SUFFIX)_SUFFIX(6)
#define ZENRepeat_7(_PREFIX, _SUFFIX)	_PREFIX(7)ZENRepeat_6(_PREFIX, _SUFFIX)_SUFFIX(7)
#define ZENRepeat_8(_PREFIX, _SUFFIX)	_PREFIX(8)ZENRepeat_7(_PREFIX, _SUFFIX)_SUFFIX(8)
#define ZENRepeat_9(_PREFIX, _SUFFIX)	_PREFIX(9)ZENRepeat_8(_PREFIX, _SUFFIX)_SUFFIX(9)

#define ZENRepeat_10(_PREFIX, _SUFFIX)	_PREFIX(10)ZENRepeat_9(_PREFIX, _SUFFIX)_SUFFIX(10)
#define ZENRepeat_11(_PREFIX, _SUFFIX)	_PREFIX(11)ZENRepeat_10(_PREFIX, _SUFFIX)_SUFFIX(11)
#define ZENRepeat_12(_PREFIX, _SUFFIX)	_PREFIX(12)ZENRepeat_11(_PREFIX, _SUFFIX)_SUFFIX(12)
#define ZENRepeat_13(_PREFIX, _SUFFIX)	_PREFIX(13)ZENRepeat_12(_PREFIX, _SUFFIX)_SUFFIX(13)
#define ZENRepeat_14(_PREFIX, _SUFFIX)	_PREFIX(14)ZENRepeat_13(_PREFIX, _SUFFIX)_SUFFIX(14)
#define ZENRepeat_15(_PREFIX, _SUFFIX)	_PREFIX(15)ZENRepeat_14(_PREFIX, _SUFFIX)_SUFFIX(15)
#define ZENRepeat_16(_PREFIX, _SUFFIX)	_PREFIX(16)ZENRepeat_15(_PREFIX, _SUFFIX)_SUFFIX(16)
#define ZENRepeat_17(_PREFIX, _SUFFIX)	_PREFIX(17)ZENRepeat_16(_PREFIX, _SUFFIX)_SUFFIX(17)
#define ZENRepeat_18(_PREFIX, _SUFFIX)	_PREFIX(18)ZENRepeat_17(_PREFIX, _SUFFIX)_SUFFIX(18)
#define ZENRepeat_19(_PREFIX, _SUFFIX)	_PREFIX(19)ZENRepeat_18(_PREFIX, _SUFFIX)_SUFFIX(19)

#define ZENRepeat_20(_PREFIX, _SUFFIX)	_PREFIX(20)ZENRepeat_19(_PREFIX, _SUFFIX)_SUFFIX(20)
#define ZENRepeat_21(_PREFIX, _SUFFIX)	_PREFIX(21)ZENRepeat_20(_PREFIX, _SUFFIX)_SUFFIX(21)
#define ZENRepeat_22(_PREFIX, _SUFFIX)	_PREFIX(22)ZENRepeat_21(_PREFIX, _SUFFIX)_SUFFIX(22)
#define ZENRepeat_23(_PREFIX, _SUFFIX)	_PREFIX(23)ZENRepeat_22(_PREFIX, _SUFFIX)_SUFFIX(23)
#define ZENRepeat_24(_PREFIX, _SUFFIX)	_PREFIX(24)ZENRepeat_23(_PREFIX, _SUFFIX)_SUFFIX(24)
#define ZENRepeat_25(_PREFIX, _SUFFIX)	_PREFIX(25)ZENRepeat_24(_PREFIX, _SUFFIX)_SUFFIX(25)
#define ZENRepeat_26(_PREFIX, _SUFFIX)	_PREFIX(26)ZENRepeat_25(_PREFIX, _SUFFIX)_SUFFIX(26)
#define ZENRepeat_27(_PREFIX, _SUFFIX)	_PREFIX(27)ZENRepeat_26(_PREFIX, _SUFFIX)_SUFFIX(27)
#define ZENRepeat_28(_PREFIX, _SUFFIX)	_PREFIX(28)ZENRepeat_27(_PREFIX, _SUFFIX)_SUFFIX(28)
#define ZENRepeat_29(_PREFIX, _SUFFIX)	_PREFIX(29)ZENRepeat_28(_PREFIX, _SUFFIX)_SUFFIX(29)

#define ZENRepeat_30(_PREFIX, _SUFFIX)	_PREFIX(30)ZENRepeat_29(_PREFIX, _SUFFIX)_SUFFIX(30)
#define ZENRepeat_31(_PREFIX, _SUFFIX)	_PREFIX(31)ZENRepeat_30(_PREFIX, _SUFFIX)_SUFFIX(31)
#define ZENRepeat_32(_PREFIX, _SUFFIX)	_PREFIX(32)ZENRepeat_31(_PREFIX, _SUFFIX)_SUFFIX(32)
#define ZENRepeat_33(_PREFIX, _SUFFIX)	_PREFIX(33)ZENRepeat_32(_PREFIX, _SUFFIX)_SUFFIX(33)
#define ZENRepeat_34(_PREFIX, _SUFFIX)	_PREFIX(34)ZENRepeat_33(_PREFIX, _SUFFIX)_SUFFIX(34)
#define ZENRepeat_35(_PREFIX, _SUFFIX)	_PREFIX(35)ZENRepeat_34(_PREFIX, _SUFFIX)_SUFFIX(35)
#define ZENRepeat_36(_PREFIX, _SUFFIX)	_PREFIX(36)ZENRepeat_35(_PREFIX, _SUFFIX)_SUFFIX(36)
#define ZENRepeat_37(_PREFIX, _SUFFIX)	_PREFIX(37)ZENRepeat_36(_PREFIX, _SUFFIX)_SUFFIX(37)
#define ZENRepeat_38(_PREFIX, _SUFFIX)	_PREFIX(38)ZENRepeat_37(_PREFIX, _SUFFIX)_SUFFIX(38)
#define ZENRepeat_39(_PREFIX, _SUFFIX)	_PREFIX(39)ZENRepeat_38(_PREFIX, _SUFFIX)_SUFFIX(39)

#define ZENRepeat_40(_PREFIX, _SUFFIX)	_PREFIX(40)ZENRepeat_39(_PREFIX, _SUFFIX)_SUFFIX(40)
#define ZENRepeat_41(_PREFIX, _SUFFIX)	_PREFIX(41)ZENRepeat_40(_PREFIX, _SUFFIX)_SUFFIX(41)
#define ZENRepeat_42(_PREFIX, _SUFFIX)	_PREFIX(42)ZENRepeat_41(_PREFIX, _SUFFIX)_SUFFIX(42)
#define ZENRepeat_43(_PREFIX, _SUFFIX)	_PREFIX(43)ZENRepeat_42(_PREFIX, _SUFFIX)_SUFFIX(43)
#define ZENRepeat_44(_PREFIX, _SUFFIX)	_PREFIX(44)ZENRepeat_43(_PREFIX, _SUFFIX)_SUFFIX(44)
#define ZENRepeat_45(_PREFIX, _SUFFIX)	_PREFIX(45)ZENRepeat_44(_PREFIX, _SUFFIX)_SUFFIX(45)
#define ZENRepeat_46(_PREFIX, _SUFFIX)	_PREFIX(46)ZENRepeat_45(_PREFIX, _SUFFIX)_SUFFIX(46)
#define ZENRepeat_47(_PREFIX, _SUFFIX)	_PREFIX(47)ZENRepeat_46(_PREFIX, _SUFFIX)_SUFFIX(47)
#define ZENRepeat_48(_PREFIX, _SUFFIX)	_PREFIX(48)ZENRepeat_47(_PREFIX, _SUFFIX)_SUFFIX(48)
#define ZENRepeat_49(_PREFIX, _SUFFIX)	_PREFIX(49)ZENRepeat_48(_PREFIX, _SUFFIX)_SUFFIX(49)

#define ZENRepeat_50(_PREFIX, _SUFFIX)	_PREFIX(50)ZENRepeat_49(_PREFIX, _SUFFIX)_SUFFIX(50)
#define ZENRepeat_51(_PREFIX, _SUFFIX)	_PREFIX(51)ZENRepeat_50(_PREFIX, _SUFFIX)_SUFFIX(51)
#define ZENRepeat_52(_PREFIX, _SUFFIX)	_PREFIX(52)ZENRepeat_51(_PREFIX, _SUFFIX)_SUFFIX(52)
#define ZENRepeat_53(_PREFIX, _SUFFIX)	_PREFIX(53)ZENRepeat_52(_PREFIX, _SUFFIX)_SUFFIX(53)
#define ZENRepeat_54(_PREFIX, _SUFFIX)	_PREFIX(54)ZENRepeat_53(_PREFIX, _SUFFIX)_SUFFIX(54)
#define ZENRepeat_55(_PREFIX, _SUFFIX)	_PREFIX(55)ZENRepeat_54(_PREFIX, _SUFFIX)_SUFFIX(55)
#define ZENRepeat_56(_PREFIX, _SUFFIX)	_PREFIX(56)ZENRepeat_55(_PREFIX, _SUFFIX)_SUFFIX(56)
#define ZENRepeat_57(_PREFIX, _SUFFIX)	_PREFIX(57)ZENRepeat_56(_PREFIX, _SUFFIX)_SUFFIX(57)
#define ZENRepeat_58(_PREFIX, _SUFFIX)	_PREFIX(58)ZENRepeat_57(_PREFIX, _SUFFIX)_SUFFIX(58)
#define ZENRepeat_59(_PREFIX, _SUFFIX)	_PREFIX(59)ZENRepeat_58(_PREFIX, _SUFFIX)_SUFFIX(59)

#define ZENRepeat_60(_PREFIX, _SUFFIX)	_PREFIX(60)ZENRepeat_59(_PREFIX, _SUFFIX)_SUFFIX(60)
#define ZENRepeat_61(_PREFIX, _SUFFIX)	_PREFIX(61)ZENRepeat_60(_PREFIX, _SUFFIX)_SUFFIX(61)
#define ZENRepeat_62(_PREFIX, _SUFFIX)	_PREFIX(62)ZENRepeat_61(_PREFIX, _SUFFIX)_SUFFIX(62)
#define ZENRepeat_63(_PREFIX, _SUFFIX)	_PREFIX(63)ZENRepeat_62(_PREFIX, _SUFFIX)_SUFFIX(63)
#define ZENRepeat_64(_PREFIX, _SUFFIX)	_PREFIX(64)ZENRepeat_63(_PREFIX, _SUFFIX)_SUFFIX(64)
#define ZENRepeat_65(_PREFIX, _SUFFIX)	_PREFIX(65)ZENRepeat_64(_PREFIX, _SUFFIX)_SUFFIX(65)
#define ZENRepeat_66(_PREFIX, _SUFFIX)	_PREFIX(66)ZENRepeat_65(_PREFIX, _SUFFIX)_SUFFIX(66)
#define ZENRepeat_67(_PREFIX, _SUFFIX)	_PREFIX(67)ZENRepeat_66(_PREFIX, _SUFFIX)_SUFFIX(67)
#define ZENRepeat_68(_PREFIX, _SUFFIX)	_PREFIX(68)ZENRepeat_67(_PREFIX, _SUFFIX)_SUFFIX(68)
#define ZENRepeat_69(_PREFIX, _SUFFIX)	_PREFIX(69)ZENRepeat_68(_PREFIX, _SUFFIX)_SUFFIX(69)

#define ZENRepeat_70(_PREFIX, _SUFFIX)	_PREFIX(70)ZENRepeat_69(_PREFIX, _SUFFIX)_SUFFIX(70)
#define ZENRepeat_71(_PREFIX, _SUFFIX)	_PREFIX(71)ZENRepeat_70(_PREFIX, _SUFFIX)_SUFFIX(71)
#define ZENRepeat_72(_PREFIX, _SUFFIX)	_PREFIX(72)ZENRepeat_71(_PREFIX, _SUFFIX)_SUFFIX(72)
#define ZENRepeat_73(_PREFIX, _SUFFIX)	_PREFIX(73)ZENRepeat_72(_PREFIX, _SUFFIX)_SUFFIX(73)
#define ZENRepeat_74(_PREFIX, _SUFFIX)	_PREFIX(74)ZENRepeat_73(_PREFIX, _SUFFIX)_SUFFIX(74)
#define ZENRepeat_75(_PREFIX, _SUFFIX)	_PREFIX(75)ZENRepeat_74(_PREFIX, _SUFFIX)_SUFFIX(75)
#define ZENRepeat_76(_PREFIX, _SUFFIX)	_PREFIX(76)ZENRepeat_75(_PREFIX, _SUFFIX)_SUFFIX(76)
#define ZENRepeat_77(_PREFIX, _SUFFIX)	_PREFIX(77)ZENRepeat_76(_PREFIX, _SUFFIX)_SUFFIX(77)
#define ZENRepeat_78(_PREFIX, _SUFFIX)	_PREFIX(78)ZENRepeat_77(_PREFIX, _SUFFIX)_SUFFIX(78)
#define ZENRepeat_79(_PREFIX, _SUFFIX)	_PREFIX(79)ZENRepeat_78(_PREFIX, _SUFFIX)_SUFFIX(79)

#define ZENRepeat_80(_PREFIX, _SUFFIX)	_PREFIX(80)ZENRepeat_79(_PREFIX, _SUFFIX)_SUFFIX(80)
#define ZENRepeat_81(_PREFIX, _SUFFIX)	_PREFIX(81)ZENRepeat_80(_PREFIX, _SUFFIX)_SUFFIX(81)
#define ZENRepeat_82(_PREFIX, _SUFFIX)	_PREFIX(82)ZENRepeat_81(_PREFIX, _SUFFIX)_SUFFIX(82)
#define ZENRepeat_83(_PREFIX, _SUFFIX)	_PREFIX(83)ZENRepeat_82(_PREFIX, _SUFFIX)_SUFFIX(83)
#define ZENRepeat_84(_PREFIX, _SUFFIX)	_PREFIX(84)ZENRepeat_83(_PREFIX, _SUFFIX)_SUFFIX(84)
#define ZENRepeat_85(_PREFIX, _SUFFIX)	_PREFIX(85)ZENRepeat_84(_PREFIX, _SUFFIX)_SUFFIX(85)
#define ZENRepeat_86(_PREFIX, _SUFFIX)	_PREFIX(86)ZENRepeat_85(_PREFIX, _SUFFIX)_SUFFIX(86)
#define ZENRepeat_87(_PREFIX, _SUFFIX)	_PREFIX(87)ZENRepeat_86(_PREFIX, _SUFFIX)_SUFFIX(87)
#define ZENRepeat_88(_PREFIX, _SUFFIX)	_PREFIX(88)ZENRepeat_87(_PREFIX, _SUFFIX)_SUFFIX(88)
#define ZENRepeat_89(_PREFIX, _SUFFIX)	_PREFIX(89)ZENRepeat_88(_PREFIX, _SUFFIX)_SUFFIX(89)

#define ZENRepeat_90(_PREFIX, _SUFFIX)	_PREFIX(90)ZENRepeat_89(_PREFIX, _SUFFIX)_SUFFIX(90)
#define ZENRepeat_91(_PREFIX, _SUFFIX)	_PREFIX(91)ZENRepeat_90(_PREFIX, _SUFFIX)_SUFFIX(91)
#define ZENRepeat_92(_PREFIX, _SUFFIX)	_PREFIX(92)ZENRepeat_91(_PREFIX, _SUFFIX)_SUFFIX(92)
#define ZENRepeat_93(_PREFIX, _SUFFIX)	_PREFIX(93)ZENRepeat_92(_PREFIX, _SUFFIX)_SUFFIX(93)
#define ZENRepeat_94(_PREFIX, _SUFFIX)	_PREFIX(94)ZENRepeat_93(_PREFIX, _SUFFIX)_SUFFIX(94)
#define ZENRepeat_95(_PREFIX, _SUFFIX)	_PREFIX(95)ZENRepeat_94(_PREFIX, _SUFFIX)_SUFFIX(95)
#define ZENRepeat_96(_PREFIX, _SUFFIX)	_PREFIX(96)ZENRepeat_95(_PREFIX, _SUFFIX)_SUFFIX(96)
#define ZENRepeat_97(_PREFIX, _SUFFIX)	_PREFIX(97)ZENRepeat_96(_PREFIX, _SUFFIX)_SUFFIX(97)
#define ZENRepeat_98(_PREFIX, _SUFFIX)	_PREFIX(98)ZENRepeat_97(_PREFIX, _SUFFIX)_SUFFIX(98)
#define ZENRepeat_99(_PREFIX, _SUFFIX)	_PREFIX(99)ZENRepeat_98(_PREFIX, _SUFFIX)_SUFFIX(99)
#define ZENRepeat_100(_PREFIX, _SUFFIX)	_PREFIX(100)ZENRepeat_99(_PREFIX, _SUFFIX)_SUFFIX(100)
//! @endcond DOXYGEN_IGNORE

#define ZENRepeat(_COUNT, _PREFIX, _SUFFIX)			ZENRepeat_##_COUNT(_PREFIX, _SUFFIX)
#define ZENRepeatString(_COUNT, _PREFIX, _SUFFIX )	ZENStringDefine( ZENRepeat_##_COUNT(_PREFIX, _SUFFIX) )
