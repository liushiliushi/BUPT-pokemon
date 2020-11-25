#include "manager.h"

Manager::Manager() //: QObject(parent)
{


    shmap["独角兽"] = ":/new/spirit/ziyuan/spirit/attack/horse/sh.png";
    shmap["石锤犀牛"] = ":/new/spirit/ziyuan/spirit/attack/ox/sh.png";
    shmap["石盾牌"] = ":/new/spirit/ziyuan/spirit/defend/rock/sh.png";
    shmap["冰蜗牛"] = ":/new/spirit/ziyuan/spirit/defend/snail/sh.png";
    shmap["紫鬃龙"] = ":/new/spirit/ziyuan/spirit/hp/dragon/sh.png";
    shmap["派大星"] = ":/new/spirit/ziyuan/spirit/hp/star/sh.png";
    shmap["咕咕鸡"] = ":/new/spirit/ziyuan/spirit/interval/bird/sh.png";
    shmap["海马先生"] = ":/new/spirit/ziyuan/spirit/interval/haima/sh.png";

    bhmap["独角兽"] = ":/new/spirit/ziyuan/spirit/attack/horse/bh.png";
    bhmap["石锤犀牛"] = ":/new/spirit/ziyuan/spirit/attack/ox/bh.png";
    bhmap["石盾牌"] = ":/new/spirit/ziyuan/spirit/defend/rock/bh.png";
    bhmap["冰蜗牛"] = ":/new/spirit/ziyuan/spirit/defend/snail/bh.png";
    bhmap["紫鬃龙"] = ":/new/spirit/ziyuan/spirit/hp/dragon/bh.png";
    bhmap["派大星"] = ":/new/spirit/ziyuan/spirit/hp/star/bh.png";
    bhmap["咕咕鸡"] = ":/new/spirit/ziyuan/spirit/interval/bird/bh.png";
    bhmap["海马先生"] = ":/new/spirit/ziyuan/spirit/interval/haima/bh.png";

    sfmap["独角兽"] = ":/new/spirit/ziyuan/spirit/attack/horse/sf.png";
    sfmap["石锤犀牛"] = ":/new/spirit/ziyuan/spirit/attack/ox/sf.png";
    sfmap["石盾牌"] = ":/new/spirit/ziyuan/spirit/defend/rock/sf.png";
    sfmap["冰蜗牛"] = ":/new/spirit/ziyuan/spirit/defend/snail/sf.png";
    sfmap["紫鬃龙"] = ":/new/spirit/ziyuan/spirit/hp/dragon/sf.png";
    sfmap["派大星"] = ":/new/spirit/ziyuan/spirit/hp/star/sf.png";
    sfmap["咕咕鸡"] = ":/new/spirit/ziyuan/spirit/interval/bird/sf.png";
    sfmap["海马先生"] = ":/new/spirit/ziyuan/spirit/interval/haima/sf.png";

    bfmap["独角兽"] = ":/new/spirit/ziyuan/spirit/attack/horse/bf.png";
    bfmap["石锤犀牛"] = ":/new/spirit/ziyuan/spirit/attack/ox/bf.png";
    bfmap["石盾牌"] = ":/new/spirit/ziyuan/spirit/defend/rock/bf.png";
    bfmap["冰蜗牛"] = ":/new/spirit/ziyuan/spirit/defend/snail/bf.png";
    bfmap["紫鬃龙"] = ":/new/spirit/ziyuan/spirit/hp/dragon/bf.png";
    bfmap["派大星"] = ":/new/spirit/ziyuan/spirit/hp/star/bf.png";
    bfmap["咕咕鸡"] = ":/new/spirit/ziyuan/spirit/interval/bird/bf.png";
    bfmap["海马先生"] = ":/new/spirit/ziyuan/spirit/interval/haima/bf.png";

    sbmap["独角兽"] = ":/new/spirit/ziyuan/spirit/attack/horse/sb.png";
    sbmap["石锤犀牛"] = ":/new/spirit/ziyuan/spirit/attack/ox/sb.png";
    sbmap["石盾牌"] = ":/new/spirit/ziyuan/spirit/defend/rock/sb.png";
    sbmap["冰蜗牛"] = ":/new/spirit/ziyuan/spirit/defend/snail/sb.png";
    sbmap["紫鬃龙"] = ":/new/spirit/ziyuan/spirit/hp/dragon/sb.png";
    sbmap["派大星"] = ":/new/spirit/ziyuan/spirit/hp/star/sb.png";
    sbmap["咕咕鸡"] = ":/new/spirit/ziyuan/spirit/interval/bird/sb.png";
    sbmap["海马先生"] = ":/new/spirit/ziyuan/spirit/interval/haima/sb.png";

    bbmap["独角兽"] = ":/new/spirit/ziyuan/spirit/attack/horse/bb.png";
    bbmap["石锤犀牛"] = ":/new/spirit/ziyuan/spirit/attack/ox/bb.png";
    bbmap["石盾牌"] = ":/new/spirit/ziyuan/spirit/defend/rock/bb.png";
    bbmap["冰蜗牛"] = ":/new/spirit/ziyuan/spirit/defend/snail/bb.png";
    bbmap["紫鬃龙"] = ":/new/spirit/ziyuan/spirit/hp/dragon/bb.png";
    bbmap["派大星"] = ":/new/spirit/ziyuan/spirit/hp/star/bb.png";
    bbmap["咕咕鸡"] = ":/new/spirit/ziyuan/spirit/interval/bird/bb.png";
    bbmap["海马先生"] = ":/new/spirit/ziyuan/spirit/interval/haima/bb.png";

    //2*图

    sf_fmap["独角兽"] = ":/new/spirit/ziyuan/spirit/attack/horse/sf_f.png";
    sf_fmap["石锤犀牛"] = ":/new/spirit/ziyuan/spirit/attack/ox/sf_f.png";
    sf_fmap["石盾牌"] = ":/new/spirit/ziyuan/spirit/defend/rock/sf_f.png";
    sf_fmap["冰蜗牛"] = ":/new/spirit/ziyuan/spirit/defend/snail/sf_f.png";
    sf_fmap["紫鬃龙"] = ":/new/spirit/ziyuan/spirit/hp/dragon/sf_f.png";
    sf_fmap["派大星"] = ":/new/spirit/ziyuan/spirit/hp/star/sf_f.png";
    sf_fmap["咕咕鸡"] = ":/new/spirit/ziyuan/spirit/interval/bird/sf_f.png";
    sf_fmap["海马先生"] = ":/new/spirit/ziyuan/spirit/interval/haima/sf_f.png";

    bf_fmap["独角兽"] = ":/new/spirit/ziyuan/spirit/attack/horse/bf_f.png";
    bf_fmap["石锤犀牛"] = ":/new/spirit/ziyuan/spirit/attack/ox/bf_f.png";
    bf_fmap["石盾牌"] = ":/new/spirit/ziyuan/spirit/defend/rock/bf_f.png";
    bf_fmap["冰蜗牛"] = ":/new/spirit/ziyuan/spirit/defend/snail/bf_f.png";
    bf_fmap["紫鬃龙"] = ":/new/spirit/ziyuan/spirit/hp/dragon/bf_f.png";
    bf_fmap["派大星"] = ":/new/spirit/ziyuan/spirit/hp/star/bf_f.png";
    bf_fmap["咕咕鸡"] = ":/new/spirit/ziyuan/spirit/interval/bird/bf_f.png";
    bf_fmap["海马先生"] = ":/new/spirit/ziyuan/spirit/interval/haima/bf_f.png";

    sb_fmap["独角兽"] = ":/new/spirit/ziyuan/spirit/attack/horse/sb_f.png";
    sb_fmap["石锤犀牛"] = ":/new/spirit/ziyuan/spirit/attack/ox/sb_f.png";
    sb_fmap["石盾牌"] = ":/new/spirit/ziyuan/spirit/defend/rock/sb_f.png";
    sb_fmap["冰蜗牛"] = ":/new/spirit/ziyuan/spirit/defend/snail/sb_f.png";
    sb_fmap["紫鬃龙"] = ":/new/spirit/ziyuan/spirit/hp/dragon/sb_f.png";
    sb_fmap["派大星"] = ":/new/spirit/ziyuan/spirit/hp/star/sb_f.png";
    sb_fmap["咕咕鸡"] = ":/new/spirit/ziyuan/spirit/interval/bird/sb_f.png";
    sb_fmap["海马先生"] = ":/new/spirit/ziyuan/spirit/interval/haima/sb_f.png";

    bb_fmap["独角兽"] = ":/new/spirit/ziyuan/spirit/attack/horse/bb_f.png";
    bb_fmap["石锤犀牛"] = ":/new/spirit/ziyuan/spirit/attack/ox/bb_f.png";
    bb_fmap["石盾牌"] = ":/new/spirit/ziyuan/spirit/defend/rock/bb_f.png";
    bb_fmap["冰蜗牛"] = ":/new/spirit/ziyuan/spirit/defend/snail/bb_f.png";
    bb_fmap["紫鬃龙"] = ":/new/spirit/ziyuan/spirit/hp/dragon/bb_f.png";
    bb_fmap["派大星"] = ":/new/spirit/ziyuan/spirit/hp/star/bb_f.png";
    bb_fmap["咕咕鸡"] = ":/new/spirit/ziyuan/spirit/interval/bird/bb_f.png";
    bb_fmap["海马先生"] = ":/new/spirit/ziyuan/spirit/interval/haima/bb_f.png";

    skill["独角兽"] = "十万马力";
    skill["石锤犀牛"] = "原始之力";
    skill["石盾牌"] = "沙暴";
    skill["冰蜗牛"] = "海妖之啸";
    skill["紫鬃龙"] = "火焰漩涡";
    skill["派大星"] = "神秘守护";
    skill["咕咕鸡"] = "空气斩";
    skill["海马先生"] = "水之波动";

    sskill["独角兽"] = "踩踏";
    sskill["石锤犀牛"] = "吼叫";
    sskill["石盾牌"] = "岩崩";
    sskill["冰蜗牛"] = "水滴攻击";
    sskill["紫鬃龙"] = "风火轮";
    sskill["派大星"] = "泡沫攻击";
    sskill["咕咕鸡"] = "羽毛舞";
    sskill["海马先生"] = "冰冻之风";


}
