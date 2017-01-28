/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x8ef4fb42 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "T:/first_lab2/x74_194.v";
static int ng1[] = {0, 0};
static int ng2[] = {1, 0};



static void Always_27_0(char *t0)
{
    char t6[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t7;
    char *t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    char *t21;
    char *t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    char *t28;
    char *t29;

LAB0:    t1 = (t0 + 2456U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(27, ng0);
    t2 = (t0 + 2796);
    *((int *)t2) = 1;
    t3 = (t0 + 2484);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(28, ng0);

LAB5:    xsi_set_current_line(29, ng0);
    t4 = (t0 + 1060U);
    t5 = *((char **)t4);
    t4 = ((char*)((ng1)));
    memset(t6, 0, 8);
    t7 = (t5 + 4);
    t8 = (t4 + 4);
    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t4);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t7);
    t13 = *((unsigned int *)t8);
    t14 = (t12 ^ t13);
    t15 = (t11 | t14);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t8);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB9;

LAB6:    if (t18 != 0)
        goto LAB8;

LAB7:    *((unsigned int *)t6) = 1;

LAB9:    t22 = (t6 + 4);
    t23 = *((unsigned int *)t22);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB10;

LAB11:
LAB12:    goto LAB2;

LAB8:    t21 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB9;

LAB10:    xsi_set_current_line(30, ng0);

LAB13:    xsi_set_current_line(31, ng0);
    t28 = ((char*)((ng1)));
    t29 = (t0 + 1656);
    xsi_vlogvar_assign_value(t29, t28, 0, 0, 1);
    xsi_set_current_line(32, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 1748);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(33, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 1840);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(34, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 1932);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    goto LAB12;

}

static void Always_38_1(char *t0)
{
    char t6[8];
    char t30[8];
    char t46[8];
    char t60[8];
    char t76[8];
    char t84[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t7;
    char *t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    char *t21;
    char *t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    char *t28;
    char *t29;
    char *t31;
    char *t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    unsigned int t44;
    char *t45;
    char *t47;
    unsigned int t48;
    unsigned int t49;
    unsigned int t50;
    unsigned int t51;
    unsigned int t52;
    char *t53;
    char *t54;
    unsigned int t55;
    unsigned int t56;
    unsigned int t57;
    char *t58;
    char *t59;
    char *t61;
    char *t62;
    unsigned int t63;
    unsigned int t64;
    unsigned int t65;
    unsigned int t66;
    unsigned int t67;
    unsigned int t68;
    unsigned int t69;
    unsigned int t70;
    unsigned int t71;
    unsigned int t72;
    unsigned int t73;
    unsigned int t74;
    char *t75;
    char *t77;
    unsigned int t78;
    unsigned int t79;
    unsigned int t80;
    unsigned int t81;
    unsigned int t82;
    char *t83;
    unsigned int t85;
    unsigned int t86;
    unsigned int t87;
    char *t88;
    char *t89;
    char *t90;
    unsigned int t91;
    unsigned int t92;
    unsigned int t93;
    unsigned int t94;
    unsigned int t95;
    unsigned int t96;
    unsigned int t97;
    char *t98;
    char *t99;
    unsigned int t100;
    unsigned int t101;
    unsigned int t102;
    unsigned int t103;
    unsigned int t104;
    unsigned int t105;
    unsigned int t106;
    unsigned int t107;
    int t108;
    int t109;
    unsigned int t110;
    unsigned int t111;
    unsigned int t112;
    unsigned int t113;
    unsigned int t114;
    unsigned int t115;
    char *t116;
    unsigned int t117;
    unsigned int t118;
    unsigned int t119;
    unsigned int t120;
    unsigned int t121;
    char *t122;
    char *t123;

LAB0:    t1 = (t0 + 2600U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(38, ng0);
    t2 = (t0 + 2804);
    *((int *)t2) = 1;
    t3 = (t0 + 2628);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(39, ng0);

LAB5:    xsi_set_current_line(40, ng0);
    t4 = (t0 + 1060U);
    t5 = *((char **)t4);
    t4 = ((char*)((ng2)));
    memset(t6, 0, 8);
    t7 = (t5 + 4);
    t8 = (t4 + 4);
    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t4);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t7);
    t13 = *((unsigned int *)t8);
    t14 = (t12 ^ t13);
    t15 = (t11 | t14);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t8);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB9;

LAB6:    if (t18 != 0)
        goto LAB8;

LAB7:    *((unsigned int *)t6) = 1;

LAB9:    t22 = (t6 + 4);
    t23 = *((unsigned int *)t22);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB10;

LAB11:
LAB12:    goto LAB2;

LAB8:    t21 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB9;

LAB10:    xsi_set_current_line(40, ng0);

LAB13:    xsi_set_current_line(41, ng0);
    t28 = (t0 + 692U);
    t29 = *((char **)t28);
    t28 = ((char*)((ng2)));
    memset(t30, 0, 8);
    t31 = (t29 + 4);
    t32 = (t28 + 4);
    t33 = *((unsigned int *)t29);
    t34 = *((unsigned int *)t28);
    t35 = (t33 ^ t34);
    t36 = *((unsigned int *)t31);
    t37 = *((unsigned int *)t32);
    t38 = (t36 ^ t37);
    t39 = (t35 | t38);
    t40 = *((unsigned int *)t31);
    t41 = *((unsigned int *)t32);
    t42 = (t40 | t41);
    t43 = (~(t42));
    t44 = (t39 & t43);
    if (t44 != 0)
        goto LAB17;

LAB14:    if (t42 != 0)
        goto LAB16;

LAB15:    *((unsigned int *)t30) = 1;

LAB17:    memset(t46, 0, 8);
    t47 = (t30 + 4);
    t48 = *((unsigned int *)t47);
    t49 = (~(t48));
    t50 = *((unsigned int *)t30);
    t51 = (t50 & t49);
    t52 = (t51 & 1U);
    if (t52 != 0)
        goto LAB18;

LAB19:    if (*((unsigned int *)t47) != 0)
        goto LAB20;

LAB21:    t54 = (t46 + 4);
    t55 = *((unsigned int *)t46);
    t56 = *((unsigned int *)t54);
    t57 = (t55 || t56);
    if (t57 > 0)
        goto LAB22;

LAB23:    memcpy(t84, t46, 8);

LAB24:    t116 = (t84 + 4);
    t117 = *((unsigned int *)t116);
    t118 = (~(t117));
    t119 = *((unsigned int *)t84);
    t120 = (t119 & t118);
    t121 = (t120 != 0);
    if (t121 > 0)
        goto LAB36;

LAB37:
LAB38:    xsi_set_current_line(48, ng0);
    t2 = (t0 + 692U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng1)));
    memset(t6, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t9 = *((unsigned int *)t3);
    t10 = *((unsigned int *)t2);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t4);
    t13 = *((unsigned int *)t5);
    t14 = (t12 ^ t13);
    t15 = (t11 | t14);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t5);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB43;

LAB40:    if (t18 != 0)
        goto LAB42;

LAB41:    *((unsigned int *)t6) = 1;

LAB43:    memset(t30, 0, 8);
    t8 = (t6 + 4);
    t23 = *((unsigned int *)t8);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 & 1U);
    if (t27 != 0)
        goto LAB44;

LAB45:    if (*((unsigned int *)t8) != 0)
        goto LAB46;

LAB47:    t22 = (t30 + 4);
    t33 = *((unsigned int *)t30);
    t34 = *((unsigned int *)t22);
    t35 = (t33 || t34);
    if (t35 > 0)
        goto LAB48;

LAB49:    memcpy(t76, t30, 8);

LAB50:    t75 = (t76 + 4);
    t95 = *((unsigned int *)t75);
    t96 = (~(t95));
    t97 = *((unsigned int *)t76);
    t100 = (t97 & t96);
    t101 = (t100 != 0);
    if (t101 > 0)
        goto LAB62;

LAB63:
LAB64:    xsi_set_current_line(55, ng0);
    t2 = (t0 + 692U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng2)));
    memset(t6, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t9 = *((unsigned int *)t3);
    t10 = *((unsigned int *)t2);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t4);
    t13 = *((unsigned int *)t5);
    t14 = (t12 ^ t13);
    t15 = (t11 | t14);
    t16 = *((unsigned int *)t4);
    t17 = *((unsigned int *)t5);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB69;

LAB66:    if (t18 != 0)
        goto LAB68;

LAB67:    *((unsigned int *)t6) = 1;

LAB69:    memset(t30, 0, 8);
    t8 = (t6 + 4);
    t23 = *((unsigned int *)t8);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 & 1U);
    if (t27 != 0)
        goto LAB70;

LAB71:    if (*((unsigned int *)t8) != 0)
        goto LAB72;

LAB73:    t22 = (t30 + 4);
    t33 = *((unsigned int *)t30);
    t34 = *((unsigned int *)t22);
    t35 = (t33 || t34);
    if (t35 > 0)
        goto LAB74;

LAB75:    memcpy(t76, t30, 8);

LAB76:    t75 = (t76 + 4);
    t95 = *((unsigned int *)t75);
    t96 = (~(t95));
    t97 = *((unsigned int *)t76);
    t100 = (t97 & t96);
    t101 = (t100 != 0);
    if (t101 > 0)
        goto LAB88;

LAB89:
LAB90:    goto LAB12;

LAB16:    t45 = (t30 + 4);
    *((unsigned int *)t30) = 1;
    *((unsigned int *)t45) = 1;
    goto LAB17;

LAB18:    *((unsigned int *)t46) = 1;
    goto LAB21;

LAB20:    t53 = (t46 + 4);
    *((unsigned int *)t46) = 1;
    *((unsigned int *)t53) = 1;
    goto LAB21;

LAB22:    t58 = (t0 + 600U);
    t59 = *((char **)t58);
    t58 = ((char*)((ng1)));
    memset(t60, 0, 8);
    t61 = (t59 + 4);
    t62 = (t58 + 4);
    t63 = *((unsigned int *)t59);
    t64 = *((unsigned int *)t58);
    t65 = (t63 ^ t64);
    t66 = *((unsigned int *)t61);
    t67 = *((unsigned int *)t62);
    t68 = (t66 ^ t67);
    t69 = (t65 | t68);
    t70 = *((unsigned int *)t61);
    t71 = *((unsigned int *)t62);
    t72 = (t70 | t71);
    t73 = (~(t72));
    t74 = (t69 & t73);
    if (t74 != 0)
        goto LAB28;

LAB25:    if (t72 != 0)
        goto LAB27;

LAB26:    *((unsigned int *)t60) = 1;

LAB28:    memset(t76, 0, 8);
    t77 = (t60 + 4);
    t78 = *((unsigned int *)t77);
    t79 = (~(t78));
    t80 = *((unsigned int *)t60);
    t81 = (t80 & t79);
    t82 = (t81 & 1U);
    if (t82 != 0)
        goto LAB29;

LAB30:    if (*((unsigned int *)t77) != 0)
        goto LAB31;

LAB32:    t85 = *((unsigned int *)t46);
    t86 = *((unsigned int *)t76);
    t87 = (t85 & t86);
    *((unsigned int *)t84) = t87;
    t88 = (t46 + 4);
    t89 = (t76 + 4);
    t90 = (t84 + 4);
    t91 = *((unsigned int *)t88);
    t92 = *((unsigned int *)t89);
    t93 = (t91 | t92);
    *((unsigned int *)t90) = t93;
    t94 = *((unsigned int *)t90);
    t95 = (t94 != 0);
    if (t95 == 1)
        goto LAB33;

LAB34:
LAB35:    goto LAB24;

LAB27:    t75 = (t60 + 4);
    *((unsigned int *)t60) = 1;
    *((unsigned int *)t75) = 1;
    goto LAB28;

LAB29:    *((unsigned int *)t76) = 1;
    goto LAB32;

LAB31:    t83 = (t76 + 4);
    *((unsigned int *)t76) = 1;
    *((unsigned int *)t83) = 1;
    goto LAB32;

LAB33:    t96 = *((unsigned int *)t84);
    t97 = *((unsigned int *)t90);
    *((unsigned int *)t84) = (t96 | t97);
    t98 = (t46 + 4);
    t99 = (t76 + 4);
    t100 = *((unsigned int *)t46);
    t101 = (~(t100));
    t102 = *((unsigned int *)t98);
    t103 = (~(t102));
    t104 = *((unsigned int *)t76);
    t105 = (~(t104));
    t106 = *((unsigned int *)t99);
    t107 = (~(t106));
    t108 = (t101 & t103);
    t109 = (t105 & t107);
    t110 = (~(t108));
    t111 = (~(t109));
    t112 = *((unsigned int *)t90);
    *((unsigned int *)t90) = (t112 & t110);
    t113 = *((unsigned int *)t90);
    *((unsigned int *)t90) = (t113 & t111);
    t114 = *((unsigned int *)t84);
    *((unsigned int *)t84) = (t114 & t110);
    t115 = *((unsigned int *)t84);
    *((unsigned int *)t84) = (t115 & t111);
    goto LAB35;

LAB36:    xsi_set_current_line(42, ng0);

LAB39:    xsi_set_current_line(43, ng0);
    t122 = (t0 + 876U);
    t123 = *((char **)t122);
    t122 = (t0 + 1656);
    xsi_vlogvar_assign_value(t122, t123, 0, 0, 1);
    xsi_set_current_line(44, ng0);
    t2 = (t0 + 1656);
    t3 = (t2 + 36U);
    t4 = *((char **)t3);
    t5 = (t0 + 1748);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 1);
    xsi_set_current_line(45, ng0);
    t2 = (t0 + 1748);
    t3 = (t2 + 36U);
    t4 = *((char **)t3);
    t5 = (t0 + 1840);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 1);
    xsi_set_current_line(46, ng0);
    t2 = (t0 + 1840);
    t3 = (t2 + 36U);
    t4 = *((char **)t3);
    t5 = (t0 + 1932);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 1);
    goto LAB38;

LAB42:    t7 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t7) = 1;
    goto LAB43;

LAB44:    *((unsigned int *)t30) = 1;
    goto LAB47;

LAB46:    t21 = (t30 + 4);
    *((unsigned int *)t30) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB47;

LAB48:    t28 = (t0 + 600U);
    t29 = *((char **)t28);
    t28 = ((char*)((ng2)));
    memset(t46, 0, 8);
    t31 = (t29 + 4);
    t32 = (t28 + 4);
    t36 = *((unsigned int *)t29);
    t37 = *((unsigned int *)t28);
    t38 = (t36 ^ t37);
    t39 = *((unsigned int *)t31);
    t40 = *((unsigned int *)t32);
    t41 = (t39 ^ t40);
    t42 = (t38 | t41);
    t43 = *((unsigned int *)t31);
    t44 = *((unsigned int *)t32);
    t48 = (t43 | t44);
    t49 = (~(t48));
    t50 = (t42 & t49);
    if (t50 != 0)
        goto LAB54;

LAB51:    if (t48 != 0)
        goto LAB53;

LAB52:    *((unsigned int *)t46) = 1;

LAB54:    memset(t60, 0, 8);
    t47 = (t46 + 4);
    t51 = *((unsigned int *)t47);
    t52 = (~(t51));
    t55 = *((unsigned int *)t46);
    t56 = (t55 & t52);
    t57 = (t56 & 1U);
    if (t57 != 0)
        goto LAB55;

LAB56:    if (*((unsigned int *)t47) != 0)
        goto LAB57;

LAB58:    t63 = *((unsigned int *)t30);
    t64 = *((unsigned int *)t60);
    t65 = (t63 & t64);
    *((unsigned int *)t76) = t65;
    t54 = (t30 + 4);
    t58 = (t60 + 4);
    t59 = (t76 + 4);
    t66 = *((unsigned int *)t54);
    t67 = *((unsigned int *)t58);
    t68 = (t66 | t67);
    *((unsigned int *)t59) = t68;
    t69 = *((unsigned int *)t59);
    t70 = (t69 != 0);
    if (t70 == 1)
        goto LAB59;

LAB60:
LAB61:    goto LAB50;

LAB53:    t45 = (t46 + 4);
    *((unsigned int *)t46) = 1;
    *((unsigned int *)t45) = 1;
    goto LAB54;

LAB55:    *((unsigned int *)t60) = 1;
    goto LAB58;

LAB57:    t53 = (t60 + 4);
    *((unsigned int *)t60) = 1;
    *((unsigned int *)t53) = 1;
    goto LAB58;

LAB59:    t71 = *((unsigned int *)t76);
    t72 = *((unsigned int *)t59);
    *((unsigned int *)t76) = (t71 | t72);
    t61 = (t30 + 4);
    t62 = (t60 + 4);
    t73 = *((unsigned int *)t30);
    t74 = (~(t73));
    t78 = *((unsigned int *)t61);
    t79 = (~(t78));
    t80 = *((unsigned int *)t60);
    t81 = (~(t80));
    t82 = *((unsigned int *)t62);
    t85 = (~(t82));
    t108 = (t74 & t79);
    t109 = (t81 & t85);
    t86 = (~(t108));
    t87 = (~(t109));
    t91 = *((unsigned int *)t59);
    *((unsigned int *)t59) = (t91 & t86);
    t92 = *((unsigned int *)t59);
    *((unsigned int *)t59) = (t92 & t87);
    t93 = *((unsigned int *)t76);
    *((unsigned int *)t76) = (t93 & t86);
    t94 = *((unsigned int *)t76);
    *((unsigned int *)t76) = (t94 & t87);
    goto LAB61;

LAB62:    xsi_set_current_line(49, ng0);

LAB65:    xsi_set_current_line(50, ng0);
    t77 = (t0 + 1748);
    t83 = (t77 + 36U);
    t88 = *((char **)t83);
    t89 = (t0 + 1656);
    xsi_vlogvar_assign_value(t89, t88, 0, 0, 1);
    xsi_set_current_line(51, ng0);
    t2 = (t0 + 1840);
    t3 = (t2 + 36U);
    t4 = *((char **)t3);
    t5 = (t0 + 1748);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 1);
    xsi_set_current_line(52, ng0);
    t2 = (t0 + 1932);
    t3 = (t2 + 36U);
    t4 = *((char **)t3);
    t5 = (t0 + 1840);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 1);
    xsi_set_current_line(53, ng0);
    t2 = (t0 + 784U);
    t3 = *((char **)t2);
    t2 = (t0 + 1932);
    xsi_vlogvar_assign_value(t2, t3, 0, 0, 1);
    goto LAB64;

LAB68:    t7 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t7) = 1;
    goto LAB69;

LAB70:    *((unsigned int *)t30) = 1;
    goto LAB73;

LAB72:    t21 = (t30 + 4);
    *((unsigned int *)t30) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB73;

LAB74:    t28 = (t0 + 600U);
    t29 = *((char **)t28);
    t28 = ((char*)((ng2)));
    memset(t46, 0, 8);
    t31 = (t29 + 4);
    t32 = (t28 + 4);
    t36 = *((unsigned int *)t29);
    t37 = *((unsigned int *)t28);
    t38 = (t36 ^ t37);
    t39 = *((unsigned int *)t31);
    t40 = *((unsigned int *)t32);
    t41 = (t39 ^ t40);
    t42 = (t38 | t41);
    t43 = *((unsigned int *)t31);
    t44 = *((unsigned int *)t32);
    t48 = (t43 | t44);
    t49 = (~(t48));
    t50 = (t42 & t49);
    if (t50 != 0)
        goto LAB80;

LAB77:    if (t48 != 0)
        goto LAB79;

LAB78:    *((unsigned int *)t46) = 1;

LAB80:    memset(t60, 0, 8);
    t47 = (t46 + 4);
    t51 = *((unsigned int *)t47);
    t52 = (~(t51));
    t55 = *((unsigned int *)t46);
    t56 = (t55 & t52);
    t57 = (t56 & 1U);
    if (t57 != 0)
        goto LAB81;

LAB82:    if (*((unsigned int *)t47) != 0)
        goto LAB83;

LAB84:    t63 = *((unsigned int *)t30);
    t64 = *((unsigned int *)t60);
    t65 = (t63 & t64);
    *((unsigned int *)t76) = t65;
    t54 = (t30 + 4);
    t58 = (t60 + 4);
    t59 = (t76 + 4);
    t66 = *((unsigned int *)t54);
    t67 = *((unsigned int *)t58);
    t68 = (t66 | t67);
    *((unsigned int *)t59) = t68;
    t69 = *((unsigned int *)t59);
    t70 = (t69 != 0);
    if (t70 == 1)
        goto LAB85;

LAB86:
LAB87:    goto LAB76;

LAB79:    t45 = (t46 + 4);
    *((unsigned int *)t46) = 1;
    *((unsigned int *)t45) = 1;
    goto LAB80;

LAB81:    *((unsigned int *)t60) = 1;
    goto LAB84;

LAB83:    t53 = (t60 + 4);
    *((unsigned int *)t60) = 1;
    *((unsigned int *)t53) = 1;
    goto LAB84;

LAB85:    t71 = *((unsigned int *)t76);
    t72 = *((unsigned int *)t59);
    *((unsigned int *)t76) = (t71 | t72);
    t61 = (t30 + 4);
    t62 = (t60 + 4);
    t73 = *((unsigned int *)t30);
    t74 = (~(t73));
    t78 = *((unsigned int *)t61);
    t79 = (~(t78));
    t80 = *((unsigned int *)t60);
    t81 = (~(t80));
    t82 = *((unsigned int *)t62);
    t85 = (~(t82));
    t108 = (t74 & t79);
    t109 = (t81 & t85);
    t86 = (~(t108));
    t87 = (~(t109));
    t91 = *((unsigned int *)t59);
    *((unsigned int *)t59) = (t91 & t86);
    t92 = *((unsigned int *)t59);
    *((unsigned int *)t59) = (t92 & t87);
    t93 = *((unsigned int *)t76);
    *((unsigned int *)t76) = (t93 & t86);
    t94 = *((unsigned int *)t76);
    *((unsigned int *)t76) = (t94 & t87);
    goto LAB87;

LAB88:    xsi_set_current_line(56, ng0);

LAB91:    xsi_set_current_line(57, ng0);
    t77 = (t0 + 1152U);
    t83 = *((char **)t77);
    t77 = (t0 + 1656);
    xsi_vlogvar_assign_value(t77, t83, 0, 0, 1);
    xsi_set_current_line(58, ng0);
    t2 = (t0 + 1244U);
    t3 = *((char **)t2);
    t2 = (t0 + 1748);
    xsi_vlogvar_assign_value(t2, t3, 0, 0, 1);
    xsi_set_current_line(59, ng0);
    t2 = (t0 + 1336U);
    t3 = *((char **)t2);
    t2 = (t0 + 1840);
    xsi_vlogvar_assign_value(t2, t3, 0, 0, 1);
    xsi_set_current_line(60, ng0);
    t2 = (t0 + 1428U);
    t3 = *((char **)t2);
    t2 = (t0 + 1932);
    xsi_vlogvar_assign_value(t2, t3, 0, 0, 1);
    goto LAB90;

}


extern void work_m_00000000002870762484_3456721101_init()
{
	static char *pe[] = {(void *)Always_27_0,(void *)Always_38_1};
	xsi_register_didat("work_m_00000000002870762484_3456721101", "isim/test_x74_isim_beh.exe.sim/work/m_00000000002870762484_3456721101.didat");
	xsi_register_executes(pe);
}
