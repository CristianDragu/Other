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
static const char *ng0 = "D:/CN 2/addpipe/cmp_exp.v";
static int ng1[] = {0, 0};
static unsigned int ng2[] = {0U, 0U};
static unsigned int ng3[] = {1U, 0U};



static void Always_30_0(char *t0)
{
    char t6[8];
    char t28[8];
    char t29[8];
    char t39[8];
    char t49[8];
    char t51[24];
    char t70[8];
    char t78[8];
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
    char *t30;
    char *t31;
    char *t32;
    unsigned int t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    char *t40;
    char *t41;
    char *t42;
    unsigned int t43;
    unsigned int t44;
    unsigned int t45;
    unsigned int t46;
    unsigned int t47;
    unsigned int t48;
    char *t50;
    char *t52;
    unsigned int t53;
    unsigned int t54;
    unsigned int t55;
    unsigned int t56;
    unsigned int t57;
    unsigned int t58;
    char *t59;
    char *t60;
    char *t61;
    unsigned int t62;
    unsigned int t63;
    unsigned int t64;
    unsigned int t65;
    unsigned int t66;
    unsigned int t67;
    char *t68;
    char *t69;
    char *t71;
    unsigned int t72;
    unsigned int t73;
    unsigned int t74;
    unsigned int t75;
    unsigned int t76;
    unsigned int t77;
    char *t79;
    char *t80;
    char *t81;
    char *t82;
    char *t83;
    unsigned int t84;
    unsigned int t85;
    unsigned int t86;
    unsigned int t87;
    unsigned int t88;
    unsigned int t89;
    char *t90;
    char *t91;

LAB0:    t1 = (t0 + 1720U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(30, ng0);
    t2 = (t0 + 1916);
    *((int *)t2) = 1;
    t3 = (t0 + 1748);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(31, ng0);

LAB5:    xsi_set_current_line(32, ng0);
    t4 = (t0 + 692U);
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

LAB11:    xsi_set_current_line(41, ng0);
    t2 = ((char*)((ng2)));
    t3 = (t0 + 1104);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 8);

LAB12:    goto LAB2;

LAB8:    t21 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB9;

LAB10:    xsi_set_current_line(33, ng0);

LAB13:    xsi_set_current_line(34, ng0);
    t30 = (t0 + 784U);
    t31 = *((char **)t30);
    memset(t29, 0, 8);
    t30 = (t29 + 4);
    t32 = (t31 + 4);
    t33 = *((unsigned int *)t31);
    t34 = (t33 >> 23);
    *((unsigned int *)t29) = t34;
    t35 = *((unsigned int *)t32);
    t36 = (t35 >> 23);
    *((unsigned int *)t30) = t36;
    t37 = *((unsigned int *)t29);
    *((unsigned int *)t29) = (t37 & 255U);
    t38 = *((unsigned int *)t30);
    *((unsigned int *)t30) = (t38 & 255U);
    t40 = (t0 + 876U);
    t41 = *((char **)t40);
    memset(t39, 0, 8);
    t40 = (t39 + 4);
    t42 = (t41 + 4);
    t43 = *((unsigned int *)t41);
    t44 = (t43 >> 23);
    *((unsigned int *)t39) = t44;
    t45 = *((unsigned int *)t42);
    t46 = (t45 >> 23);
    *((unsigned int *)t40) = t46;
    t47 = *((unsigned int *)t39);
    *((unsigned int *)t39) = (t47 & 255U);
    t48 = *((unsigned int *)t40);
    *((unsigned int *)t40) = (t48 & 255U);
    memset(t49, 0, 8);
    xsi_vlog_unsigned_minus(t49, 8, t29, 8, t39, 8);
    xsi_vlogtype_concat(t28, 8, 8, 1U, t49, 8);
    t50 = (t0 + 1104);
    xsi_vlogvar_assign_value(t50, t28, 0, 0, 8);
    xsi_set_current_line(35, ng0);
    t2 = (t0 + 1104);
    t3 = (t2 + 36U);
    t4 = *((char **)t3);
    memset(t6, 0, 8);
    t5 = (t6 + 4);
    t7 = (t4 + 4);
    t9 = *((unsigned int *)t4);
    t10 = (t9 >> 7);
    t11 = (t10 & 1);
    *((unsigned int *)t6) = t11;
    t12 = *((unsigned int *)t7);
    t13 = (t12 >> 7);
    t14 = (t13 & 1);
    *((unsigned int *)t5) = t14;
    t8 = ((char*)((ng2)));
    memset(t28, 0, 8);
    t21 = (t6 + 4);
    t22 = (t8 + 4);
    t15 = *((unsigned int *)t6);
    t16 = *((unsigned int *)t8);
    t17 = (t15 ^ t16);
    t18 = *((unsigned int *)t21);
    t19 = *((unsigned int *)t22);
    t20 = (t18 ^ t19);
    t23 = (t17 | t20);
    t24 = *((unsigned int *)t21);
    t25 = *((unsigned int *)t22);
    t26 = (t24 | t25);
    t27 = (~(t26));
    t33 = (t23 & t27);
    if (t33 != 0)
        goto LAB17;

LAB14:    if (t26 != 0)
        goto LAB16;

LAB15:    *((unsigned int *)t28) = 1;

LAB17:    t31 = (t28 + 4);
    t34 = *((unsigned int *)t31);
    t35 = (~(t34));
    t36 = *((unsigned int *)t28);
    t37 = (t36 & t35);
    t38 = (t37 != 0);
    if (t38 > 0)
        goto LAB18;

LAB19:    xsi_set_current_line(38, ng0);
    t2 = (t0 + 876U);
    t3 = *((char **)t2);
    memset(t6, 0, 8);
    t2 = (t6 + 4);
    t4 = (t3 + 4);
    t9 = *((unsigned int *)t3);
    t10 = (t9 >> 0);
    *((unsigned int *)t6) = t10;
    t11 = *((unsigned int *)t4);
    t12 = (t11 >> 0);
    *((unsigned int *)t2) = t12;
    t13 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t13 & 4294967295U);
    t14 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t14 & 4294967295U);
    t5 = (t0 + 876U);
    t7 = *((char **)t5);
    memset(t28, 0, 8);
    t5 = (t28 + 4);
    t8 = (t7 + 4);
    t15 = *((unsigned int *)t7);
    t16 = (t15 >> 31);
    t17 = (t16 & 1);
    *((unsigned int *)t28) = t17;
    t18 = *((unsigned int *)t8);
    t19 = (t18 >> 31);
    t20 = (t19 & 1);
    *((unsigned int *)t5) = t20;
    t21 = (t0 + 784U);
    t22 = *((char **)t21);
    memset(t29, 0, 8);
    t21 = (t29 + 4);
    t30 = (t22 + 4);
    t23 = *((unsigned int *)t22);
    t24 = (t23 >> 0);
    *((unsigned int *)t29) = t24;
    t25 = *((unsigned int *)t30);
    t26 = (t25 >> 0);
    *((unsigned int *)t21) = t26;
    t27 = *((unsigned int *)t29);
    *((unsigned int *)t29) = (t27 & 8388607U);
    t33 = *((unsigned int *)t21);
    *((unsigned int *)t21) = (t33 & 8388607U);
    t31 = (t0 + 784U);
    t32 = *((char **)t31);
    memset(t39, 0, 8);
    t31 = (t39 + 4);
    t40 = (t32 + 4);
    t34 = *((unsigned int *)t32);
    t35 = (t34 >> 31);
    t36 = (t35 & 1);
    *((unsigned int *)t39) = t36;
    t37 = *((unsigned int *)t40);
    t38 = (t37 >> 31);
    t43 = (t38 & 1);
    *((unsigned int *)t31) = t43;
    t41 = (t0 + 1104);
    t42 = (t41 + 36U);
    t50 = *((char **)t42);
    memset(t49, 0, 8);
    t52 = (t49 + 4);
    t59 = (t50 + 4);
    t44 = *((unsigned int *)t50);
    t45 = (t44 >> 0);
    *((unsigned int *)t49) = t45;
    t46 = *((unsigned int *)t59);
    t47 = (t46 >> 0);
    *((unsigned int *)t52) = t47;
    t48 = *((unsigned int *)t49);
    *((unsigned int *)t49) = (t48 & 255U);
    t53 = *((unsigned int *)t52);
    *((unsigned int *)t52) = (t53 & 255U);
    t60 = ((char*)((ng2)));
    xsi_vlogtype_concat(t51, 66, 66, 6U, t60, 1, t49, 8, t39, 1, t29, 23, t28, 1, t6, 32);
    t61 = (t0 + 1196);
    xsi_vlogvar_assign_value(t61, t51, 0, 0, 32);

LAB20:    goto LAB12;

LAB16:    t30 = (t28 + 4);
    *((unsigned int *)t28) = 1;
    *((unsigned int *)t30) = 1;
    goto LAB17;

LAB18:    xsi_set_current_line(36, ng0);
    t32 = (t0 + 876U);
    t40 = *((char **)t32);
    memset(t29, 0, 8);
    t32 = (t29 + 4);
    t41 = (t40 + 4);
    t43 = *((unsigned int *)t40);
    t44 = (t43 >> 0);
    *((unsigned int *)t29) = t44;
    t45 = *((unsigned int *)t41);
    t46 = (t45 >> 0);
    *((unsigned int *)t32) = t46;
    t47 = *((unsigned int *)t29);
    *((unsigned int *)t29) = (t47 & 4294967295U);
    t48 = *((unsigned int *)t32);
    *((unsigned int *)t32) = (t48 & 4294967295U);
    t42 = (t0 + 876U);
    t50 = *((char **)t42);
    memset(t39, 0, 8);
    t42 = (t39 + 4);
    t52 = (t50 + 4);
    t53 = *((unsigned int *)t50);
    t54 = (t53 >> 31);
    t55 = (t54 & 1);
    *((unsigned int *)t39) = t55;
    t56 = *((unsigned int *)t52);
    t57 = (t56 >> 31);
    t58 = (t57 & 1);
    *((unsigned int *)t42) = t58;
    t59 = (t0 + 784U);
    t60 = *((char **)t59);
    memset(t49, 0, 8);
    t59 = (t49 + 4);
    t61 = (t60 + 4);
    t62 = *((unsigned int *)t60);
    t63 = (t62 >> 0);
    *((unsigned int *)t49) = t63;
    t64 = *((unsigned int *)t61);
    t65 = (t64 >> 0);
    *((unsigned int *)t59) = t65;
    t66 = *((unsigned int *)t49);
    *((unsigned int *)t49) = (t66 & 8388607U);
    t67 = *((unsigned int *)t59);
    *((unsigned int *)t59) = (t67 & 8388607U);
    t68 = (t0 + 784U);
    t69 = *((char **)t68);
    memset(t70, 0, 8);
    t68 = (t70 + 4);
    t71 = (t69 + 4);
    t72 = *((unsigned int *)t69);
    t73 = (t72 >> 31);
    t74 = (t73 & 1);
    *((unsigned int *)t70) = t74;
    t75 = *((unsigned int *)t71);
    t76 = (t75 >> 31);
    t77 = (t76 & 1);
    *((unsigned int *)t68) = t77;
    t79 = (t0 + 1104);
    t80 = (t79 + 36U);
    t81 = *((char **)t80);
    memset(t78, 0, 8);
    t82 = (t78 + 4);
    t83 = (t81 + 4);
    t84 = *((unsigned int *)t81);
    t85 = (t84 >> 0);
    *((unsigned int *)t78) = t85;
    t86 = *((unsigned int *)t83);
    t87 = (t86 >> 0);
    *((unsigned int *)t82) = t87;
    t88 = *((unsigned int *)t78);
    *((unsigned int *)t78) = (t88 & 255U);
    t89 = *((unsigned int *)t82);
    *((unsigned int *)t82) = (t89 & 255U);
    t90 = ((char*)((ng3)));
    xsi_vlogtype_concat(t51, 66, 66, 6U, t90, 1, t78, 8, t70, 1, t49, 23, t39, 1, t29, 32);
    t91 = (t0 + 1196);
    xsi_vlogvar_assign_value(t91, t51, 0, 0, 32);
    goto LAB20;

}


extern void work_m_00000000000641550145_1490026560_init()
{
	static char *pe[] = {(void *)Always_30_0};
	xsi_register_didat("work_m_00000000000641550145_1490026560", "isim/test_cmp_exp_isim_beh.exe.sim/work/m_00000000000641550145_1490026560.didat");
	xsi_register_executes(pe);
}
