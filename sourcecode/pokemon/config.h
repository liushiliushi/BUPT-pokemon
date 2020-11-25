#ifndef CONFIG_H
#define CONFIG_H
#pragma execution_character_set("utf-8")
#define INC 10 //升级后的增量
#define GAME_WIDTH 1280
#define GAME_HEIGHT 720
#define GAME_TITLE "口袋精灵"
#define BACKGROUND_PATH ":/new/background/ziyuan/background/1.jpg" //进入背景
#define LOG_PATH ":/new/background/ziyuan/background/river.jpg" //登陆背景
#define LOBBY_PATH ":/new/background/ziyuan/background/room1.jpg"
#define GAME_ICON_PATH ""
#define STARTBTN0 ":/new/button/ziyuan/button/start.png"  //开始按钮

/**************游戏大厅****************/
#define ZHI_PATH ":/new/character/ziyuan/character/zhi2.png" //小智
#define NAME_PATH ":/new/button/ziyuan/button/name.png"  //名字栏
#define USERS_PATH ":/new/button/ziyuan/button/lists.png"  //用户列表按钮
#define BAG_PATH ":/new/button/ziyuan/button/bag.png"  //背包按钮
#define FIGHT_PATH ":/new/button/ziyuan/button/upgrade.png"   //战役按钮
#define VS_PATH ":/new/button/ziyuan/button/fight.png"   //竞技按钮
#define ST_PATH ":/new/button/ziyuan/button/1st.png"   //1
#define ND_PATH ":/new/button/ziyuan/button/2nd.png"   //2
#define RD_PATH ":/new/button/ziyuan/button/3rd.png"   //3
#define COIN_PATH ":/new/button/ziyuan/button/coin.png" //金币
#define FRAME_PATH ":/new/button/ziyuan/button/money.png" //金币框
#define EXIT_PATH ":/new/button/ziyuan/button/exit.png" //退出按钮
#define NUM_PATH ":/new/button/ziyuan/button/num.png" //宠物个数勋章
#define GOOD_PATH ":/new/button/ziyuan/button/good.png" //高级宠物勋章

/***************用户列表****************/
#define USERLIST_PATH ":/new/button/ziyuan/button/users.png"  //用户列表弹出框
#define EXIT2_PATH ":/new/button/ziyuan/button/exit2.png"   //关闭按钮
#define UFRAME_PATH ":/new/button/ziyuan/button/frame.png"  //用户背景
#define INQ_PATH ":/new/button/ziyuan/button/add.png"   //查询按钮

/****************用户信息*******************/
#define USERINFO_PATH ":/new/button/ziyuan/button/frame2.png"

/*****************精灵背包*******************/
#define BAGWIDGET_PATH ":/new/background/ziyuan/background/room2.jpg" //背景图
#define RET_PATH ":/new/button/ziyuan/button/back.png"   //返回按钮
#define SPIRIT_PATH ":/new/spirit/ziyuan/spirit/025Pikachu.png" //精灵
#define FRAME2_PATH ":/new/button/ziyuan/button/spiritFrame.png"  //精灵卡片

/*****************精灵信息********************/
#define SPIRITINFO_PATH ":/new/button/ziyuan/button/spirit_info.png"

/********************对战界面*********************/
#define FIGHT1 ":/new/background/ziyuan/background/fight1.jpg"
#define FIGHT2 ":/new/background/ziyuan/background/fight2.jpg"
#define HP_LEFT ":/new/button/ziyuan/button/intro.png"
#define HP_RIGHT ":/new/button/ziyuan/button/intro2.png"

/********************选择界面********************/
#define CHOOSE_PATH ":/new/background/ziyuan/background/choose.jpg"

/*****************精灵属性********************/
#define ATTACK 0 //攻击型
#define DEFEND 1 //防御型
#define HP 2 //肉盾型
#define INTERVAL 3 //敏捷型

/********************结果界面**********************/
#define WIN_VS_PATH   ":/new/button/ziyuan/button/winspirit.png"
#define WIN_FIGHT_PATH   ":/new/button/ziyuan/button/winplus.png"
#define FAIL_VS_PATH ":/new/button/ziyuan/button/failadopt.png"
#define FAIL_FIGHT_PATH ":/new/button/ziyuan/button/fail.png"
#define PING_PATH ":/new/button/ziyuan/button/ping.png"

/******************socket通信**********************/
#define LOGIN "0"
#define LOGIN_SUCCEED "01"
#define LOGIN_FAILED "02"
#define SIGNOUT "03"
#define SIGNIN "1"
#define SIGNIN_SUCCEED "11"
#define SIGNIN_FAILED "12"
#define LOBBY "3"
#define LOBBY_SUCCEED "31"
#define LOBBY_FAILED "32"
#define USERLIST "4"
#define USERINFO "5"
#define BAG "6"
#define SPIRINTINFO "7"
#define SPIRIT_UP "71"
#define SKILL_UP "72"
#define SPIRIT_UPGRADE "73"
#define CHOOSE "8"
#define FIGHT_USER "9"
#define RESULT "10"
#define RESULT_VS_FAIL "101"
#define RESULT_FIGHT_FAIL "102"
#define RESULT_VS_WIN "103"
#define RESULT_FIGHT_WIN "104"
#define ADOPT "105"
#define ADOPTONE "106"

#endif // CONFIG_H
#ifndef CONFIG_H
#define CONFIG_H

#endif // CONFIG_H
