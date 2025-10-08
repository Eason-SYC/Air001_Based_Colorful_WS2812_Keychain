#include "manage.h"

static unsigned long battery_overlay_start_time = 0;
static BatteryLevel battery_level_snapshot;
const unsigned long CHARGING_ICON_INTERVAL = 300; 
// 动画总共有5个图标，播放2遍，所以总共是 10 帧
const unsigned long CHARGING_ANIM_DURATION = CHARGING_ICON_INTERVAL * 10;
// 动画开始计时器
static unsigned long charging_anim_start_time = 0;
static uint8_t preview_brightness_level;

AppState appState = {
    .main_mode = MainMode::ANIMATION,
    .anim_mode = AnimMode::FLAME,
    .pic_mode  = PicMode::CAT,
    .game_mode = GameMode::PINBALL,
    .letter_mode = LetterMode::Letter_A,
    .number_mode = NumberMode::Number_0,
    .tool_mode = ToolMode::SETTINGS,
    .overlay_mode = SystemOverlayMode::NONE,
    .in_sub_menu = false,
    .is_game_running = false,
    .brightness_level = 1 // 假设亮度0,1,2, 初始为中间档
};

const int BRIGHTNESS_EEPROM_ADDR = 0;

// ★★★ 新增：从 EEPROM 读取亮度的函数 ★★★
void load_brightness_from_eeprom() {
    // 1. 从地址 0 读取一个字节
    uint8_t saved_level = EEPROM.read(BRIGHTNESS_EEPROM_ADDR);

    // 2. 合法性检查：EEPROM 默认值是 255 (0xFF)。
    //    如果读取的值超出了我们的范围(0-4)，说明是第一次启动或数据无效。
    if (saved_level >= 0 && saved_level <= 4) {
        appState.brightness_level = saved_level;
    } else {
        // 如果数据无效，就设置一个默认值 (比如中等亮度2)
        appState.brightness_level = 2;
    }
}

// ★★★ 新增：将亮度写入 EEPROM 的函数 ★★★
void save_brightness_to_eeprom(uint8_t level) {
    // 为了避免不必要的擦写损耗，只有在值发生变化时才写入
    if (EEPROM.read(BRIGHTNESS_EEPROM_ADDR) != level) {
        EEPROM.write(BRIGHTNESS_EEPROM_ADDR, level);
    }
}

//======================================================================
//   核心：输入处理函数 (State Changer) - [重构后版本]
//======================================================================
void handle_input() {
    KeyEvent event = read_key_event();
    if (event == KeyEvent::NO_EVENT) return;

    // --- 优先级 1: 如果正在显示电量，则忽略所有按键输入 ---
    if (appState.overlay_mode == SystemOverlayMode::BATTERY_DISPLAY) {
        return; 
    }

    // --- 优先级 2: 处理“双键按下”这个全局事件 ---
    if (event == KeyEvent::BOTH_PRESS) {
        bool is_actual_game_active = (appState.main_mode == MainMode::GAME && appState.is_game_running);
        if (!is_actual_game_active) {
            appState.overlay_mode = SystemOverlayMode::BATTERY_DISPLAY;
            battery_overlay_start_time = millis();
            battery_level_snapshot = getCurrentBatteryLevel();
        }
        return; 
    }

    // --- 优先级 3: 处理全屏运行状态 (动画/图片/游戏) ---
    if (appState.is_game_running) {
        // ---- 动画模式下的特殊处理 ----
        if (appState.main_mode == MainMode::ANIMATION) {
            if (event == KeyEvent::LEFT_CLICK) {
                // 左键单击，切换到下一个动画
                appState.anim_mode = static_cast<AnimMode>(((int)appState.anim_mode + 1) % 4);
            }
            // 右键单击（确认键）在此处无效，直接忽略。
        }
        if (appState.main_mode == MainMode::PIC) {
            if (event == KeyEvent::LEFT_CLICK) {
                // 左键单击，切换到下一个动画
                appState.pic_mode = static_cast<PicMode>(((int)appState.pic_mode + 1) % 6);
            }
            // 右键单击（确认键）在此处无效，直接忽略。
        } 
        if (appState.main_mode == MainMode::LETTER) {
            if (event == KeyEvent::LEFT_CLICK) {
                // 左键单击，切换到下一个动画
                appState.letter_mode = static_cast<LetterMode>(((int)appState.letter_mode + 1) % 26);
            }
            // 右键单击（确认键）在此处无效，直接忽略。
        }
        if (appState.main_mode == MainMode::NUMBER) {
            if (event == KeyEvent::LEFT_CLICK) {
                // 左键单击，切换到下一个动画
                appState.number_mode = static_cast<NumberMode>(((int)appState.number_mode + 1) % 10);
            }
            // 右键单击（确认键）在此处无效，直接忽略。
        }
        // ---- 游戏模式下的处理 (保持或待实现) ----
        else if (appState.main_mode == MainMode::GAME) {
            // 这里可以把按键事件传递给具体游戏，用于控制
            game_handle_input(event); 
        }

        // ---- 通用的退出逻辑 ----
        if (event == KeyEvent::RIGHT_LONG_PRESS) {
            appState.is_game_running = false;
            appState.in_sub_menu = false;
            
            // ★★★ 可选的强化：在退出游戏时，调用其初始化函数来重置内部状态 ★★★
            if (appState.main_mode == MainMode::GAME) {
                switch(appState.game_mode) {
                    case GameMode::SNAKE:   snake_init();   break;
                    case GameMode::PINBALL: pinball_init(); break;
                    // 其他游戏...
                }
            }
            if(appState.main_mode == MainMode::ANIMATION){
                meteor_animation_initialized = false;
            }
        }
        return; // 拦截下面的UI导航逻辑
    }

    // --- 优先级 4: 处理常规的UI菜单导航 ---
    switch (event) {
        case KeyEvent::LEFT_CLICK: // “下一个”
            if (appState.in_sub_menu) {
                switch (appState.main_mode) {
                    case MainMode::GAME:
                        appState.game_mode = static_cast<GameMode>(((int)appState.game_mode + 1) % 3);
                        break;
                    case MainMode::TOOL:
                        // ★★★ 修改：现在操作的是“预览”变量 ★★★
                        preview_brightness_level = (preview_brightness_level + 1) % 5;
                        break;
                }
            } else {
                appState.main_mode = static_cast<MainMode>(((int)appState.main_mode + 1) % 6);
            }
            break;

        case KeyEvent::RIGHT_CLICK: // “进入 / 确认”
            if (appState.main_mode == MainMode::ANIMATION || appState.main_mode == MainMode::PIC || appState.main_mode == MainMode::LETTER || appState.main_mode == MainMode::NUMBER) {
                appState.is_game_running = true;
            } else {
                if (appState.in_sub_menu) {
                    if (appState.main_mode == MainMode::GAME) {
                        appState.is_game_running = true;
                        game_start(appState.game_mode); 
                    }
                    // ★★★ 在 Tool 子菜单中，右键单击现在是“确认并退出” ★★★
                    if (appState.main_mode == MainMode::TOOL) {
                        // 1. 将最终确定的亮度值赋给全局状态
                        appState.brightness_level = preview_brightness_level;
                        // 2. 将最终值保存到 EEPROM
                        save_brightness_to_eeprom(appState.brightness_level);
                        // 3. 退出子菜单
                        appState.in_sub_menu = false;
                    }
                } else { // 如果在主菜单里
                    // ★★★ 进入 Tool 子菜单前的准备工作 ★★★
                    if (appState.main_mode == MainMode::TOOL) {
                        // 将当前的全局亮度复制给“预览”变量，作为调节的起点
                        preview_brightness_level = appState.brightness_level;
                    }
                    appState.in_sub_menu = true;
                }
            }
            break;

        case KeyEvent::RIGHT_LONG_PRESS: // “返回 / 退出”
            if (appState.in_sub_menu) {
                appState.in_sub_menu = false;
            }
            break;
    }
}

//======================================================================
//   核心：渲染函数 (State Renderer) - [已修复全局亮度问题]
//======================================================================
void render_frame() {
    // --- 步骤 0: 检查后台“开始充电”信号 ---
    if (g_charging_started_event) {
        // 如果当前没有其他覆盖层，就启动充电动画
        if (appState.overlay_mode == SystemOverlayMode::NONE) {
            appState.overlay_mode = SystemOverlayMode::CHARGING_ANIMATION;
            // ★★★ 1. 记录动画开始的时间戳 (关键步骤) ★★★
            charging_anim_start_time = millis();
        }
        // ★★★ 2. 消耗掉信号，避免重复触发 (关键步骤) ★★★
        g_charging_started_event = false;
    }

    // --- 步骤 1: 处理所有覆盖层的“超时退出”逻辑 ---
    // 这个 switch 结构确保了逻辑的清晰和独立
    switch (appState.overlay_mode) {
        case SystemOverlayMode::BATTERY_DISPLAY:
            if (millis() - battery_overlay_start_time > 2000) {
                appState.overlay_mode = SystemOverlayMode::NONE;
            }
            break;

        case SystemOverlayMode::CHARGING_ANIMATION:
            // ★★★ 3. 添加充电动画的超时判断 (关键步骤) ★★★
            if (millis() - charging_anim_start_time > CHARGING_ANIM_DURATION) {
                appState.overlay_mode = SystemOverlayMode::NONE; // 动画播放完毕，恢复正常
            }
            break;

        default:
            // 其他模式或NONE模式，我们什么都不做
            break;
    }
    
    strip.clearWs2812(); // 每帧开始前先清空屏幕

    // --- 步骤1: 优先渲染系统覆盖层 ---
    if (appState.overlay_mode != SystemOverlayMode::NONE) {
        if (appState.overlay_mode == SystemOverlayMode::BATTERY_DISPLAY) {
             render_battery_display(); 
        }
        else if (appState.overlay_mode == SystemOverlayMode::CHARGING_ANIMATION) {
             render_charging_animation();
        }
        // 注意：覆盖层也需要应用亮度，所以我们不在这里调用show和return
        // 而是让代码继续往下走
    }
    // --- 步骤2: 渲染主内容（UI菜单 或 全屏动画/游戏）---
    else { // ★★★ 使用 else 结构，保证覆盖层和主内容只渲染一个 ★★★
        if (appState.is_game_running) {
            // ---- A. 渲染全屏动画/游戏 ----
            switch (appState.main_mode) {
                case MainMode::ANIMATION:
                    switch(appState.anim_mode) {
                        case AnimMode::FLAME:   flameEffect_lowRam(strip, 30, 200, false); break;
                        case AnimMode::RAINBOW: anim_rainbow_flow(strip, 20, 2); break;
                        case AnimMode::RAINBOW_HEART:  anim_beating_heart(strip, 250); break;
                        case AnimMode::METEOR:  anim_meteor_shower(strip, 12); break;
                    }
                    break;
                case MainMode::PIC:
                    switch(appState.pic_mode) {
                        case PicMode::CAT:   strip.Draw_pic(Cat, Cat_color); break;
                        case PicMode::PEACH: strip.Draw_pic(Peach, Peach_color); break;
                        case PicMode::HEART: strip.Draw_pic(Heart, Heart_color); break;
                        case PicMode::DARK:  strip.Draw_pic(Dark, Dark_color); break;
                        case PicMode::SWORD: strip.Draw_pic(Sword, Sword_color); break;
                        case PicMode::DOG:   strip.Draw_pic(Dog, Dog_color); break;
                    }
                    break;
                case MainMode::GAME:
                    game_update_and_render(strip);
                    break;
                case MainMode::LETTER:
                    switch(appState.letter_mode) {
                        case LetterMode::Letter_A: strip.Rainbow_bitmap(20, letter_a_num); break;
                        case LetterMode::Letter_B: strip.Rainbow_bitmap(20, letter_b_num); break;
                        case LetterMode::Letter_C: strip.Rainbow_bitmap(20, letter_c_num); break;
                        case LetterMode::Letter_D: strip.Rainbow_bitmap(20, letter_d_num); break;
                        case LetterMode::Letter_E: strip.Rainbow_bitmap(20, letter_e_num); break;
                        case LetterMode::Letter_F: strip.Rainbow_bitmap(20, letter_f_num); break;
                        case LetterMode::Letter_G: strip.Rainbow_bitmap(20, letter_g_num); break;
                        case LetterMode::Letter_H: strip.Rainbow_bitmap(20, letter_h_num); break;
                        case LetterMode::Letter_I: strip.Rainbow_bitmap(20, letter_i_num); break;
                        case LetterMode::Letter_J: strip.Rainbow_bitmap(20, letter_j_num); break;
                        case LetterMode::Letter_K: strip.Rainbow_bitmap(20, letter_k_num); break;
                        case LetterMode::Letter_L: strip.Rainbow_bitmap(20, letter_l_num); break;
                        case LetterMode::Letter_M: strip.Rainbow_bitmap(20, letter_m_num); break;
                        case LetterMode::Letter_N: strip.Rainbow_bitmap(20, letter_n_num); break;
                        case LetterMode::Letter_O: strip.Rainbow_bitmap(20, letter_o_num); break;
                        case LetterMode::Letter_P: strip.Rainbow_bitmap(20, letter_p_num); break;
                        case LetterMode::Letter_Q: strip.Rainbow_bitmap(20, letter_q_num); break;
                        case LetterMode::Letter_R: strip.Rainbow_bitmap(20, letter_r_num); break;
                        case LetterMode::Letter_S: strip.Rainbow_bitmap(20, letter_s_num); break;
                        case LetterMode::Letter_T: strip.Rainbow_bitmap(20, letter_t_num); break;
                        case LetterMode::Letter_U: strip.Rainbow_bitmap(20, letter_u_num); break;
                        case LetterMode::Letter_V: strip.Rainbow_bitmap(20, letter_v_num); break;
                        case LetterMode::Letter_W: strip.Rainbow_bitmap(20, letter_w_num); break;
                        case LetterMode::Letter_X: strip.Rainbow_bitmap(20, letter_x_num); break;
                        case LetterMode::Letter_Y: strip.Rainbow_bitmap(20, letter_y_num); break;
                        case LetterMode::Letter_Z: strip.Rainbow_bitmap(20, letter_z_num); break;
                    }
                    break;
                case MainMode::NUMBER:
                    switch(appState.number_mode) {
                        case NumberMode::Number_0: strip.Rainbow_bitmap(20, number_0_num); break;
                        case NumberMode::Number_1: strip.Rainbow_bitmap(20, number_1_num); break;
                        case NumberMode::Number_2: strip.Rainbow_bitmap(20, number_2_num); break;
                        case NumberMode::Number_3: strip.Rainbow_bitmap(20, number_3_num); break;
                        case NumberMode::Number_4: strip.Rainbow_bitmap(20, number_4_num); break;
                        case NumberMode::Number_5: strip.Rainbow_bitmap(20, number_5_num); break;
                        case NumberMode::Number_6: strip.Rainbow_bitmap(20, number_6_num); break;
                        case NumberMode::Number_7: strip.Rainbow_bitmap(20, number_7_num); break;
                        case NumberMode::Number_8: strip.Rainbow_bitmap(20, number_8_num); break;
                        case NumberMode::Number_9: strip.Rainbow_bitmap(20, number_9_num); break;
                    }
                    break;
            }
        }
        else {
            // ---- B. 渲染UI导航菜单 ----
            if (appState.in_sub_menu) {
                switch (appState.main_mode) {
                    case MainMode::GAME: draw_game_icon(appState.game_mode); break;
                    case MainMode::TOOL: draw_tool_icon(appState.tool_mode); break;
                }
            } else {
                draw_main_menu_icon(appState.main_mode);
            }
        }
    }

    uint8_t real_brightness;
    // ★★★ 核心修改：判断当前是否在设置界面 ★★★
    uint8_t level_to_render = (appState.main_mode == MainMode::TOOL && appState.in_sub_menu) 
                              ? preview_brightness_level  // 在设置界面，使用预览值
                              : appState.brightness_level;  // 其他所有情况，使用全局值

    switch(level_to_render) {
        case 0: real_brightness = 30;  break;
        case 1: real_brightness = 60;  break;
        case 2: real_brightness = 90;  break;
        case 3: real_brightness = 160; break;
        case 4: real_brightness = 255; break;
        default: real_brightness = 90;
    }
    strip.setBrightness(real_brightness);
    strip.Ws2812_show();
}

void render_battery_display() {
    BatteryLevel level = battery_level_snapshot;
    
    switch (level) {
        case LEVEL_FULL: // 5格电 (绿色)
            strip.Draw_pic(LEVEL_FULL_num, LEVEL_FULL_color);
            break;
            
        case LEVEL_HIGH: // 4格电 (绿色)
            strip.Draw_pic(LEVEL_HIGH_num, LEVEL_HIGH_color);
            break;
            
        case LEVEL_MEDIUM: // 3格电 (黄色)
            strip.Draw_pic(LEVEL_MEDIUM_num, LEVEL_MEDIUM_color);
            break;
            
        case LEVEL_LOW: // 2格电 (红色)
            strip.Draw_pic(LEVEL_LOW_num, LEVEL_LOW_color);
            break;

        case LEVEL_EMPTY: // 1格电 (红色闪烁)
            if ((millis() / 300) % 2 == 0) { // 每300ms切换一次状态
                strip.Draw_pic(LEVEL_EMPTY_num_1, LEVEL_EMPTY_color_1);
            }else
            {
                strip.Draw_pic(LEVEL_EMPTY_num_2, LEVEL_EMPTY_color_2);
            }
            break;
    }
}

//======================================================================
//   辅助：图标“绘制”函数 (使用串口进行调试)
//======================================================================
// 这些函数现在不操作 strip 对象，只打印信息到串口

void draw_main_menu_icon(MainMode mode) {
    switch(mode) {
        case MainMode::ANIMATION: anim_logo(strip, 250); break;
        case MainMode::PIC:       strip.Draw_pic(pic_icon_num, pic_icon_color);   break;
        case MainMode::GAME:      strip.Draw_pic(snake_icon_num, snake_icon_color);  break;
        case MainMode::LETTER:    strip.Rainbow_bitmap(20, letter_icon_num);break;
        case MainMode::NUMBER:    strip.Rainbow_bitmap(20, number_icon_num);break;
        case MainMode::TOOL:      strip.Rainbow_bitmap(20, tool_icon_num);  break;
    }
}

void draw_game_icon(GameMode mode) {
    switch(mode) {
        case GameMode::PINBALL:      
            draw_pinball_icon(strip); 
            break;
        case GameMode::SNAKE:        
            draw_snake_icon(strip);
            break;
        case GameMode::GAME_OF_LIFE: 
            draw_gol_icon(strip, 250);
            break;
    }
}

void draw_tool_icon(ToolMode mode) {
    draw_brightness_icon(preview_brightness_level);
}

void render_charging_animation() {
    // 1. 计算从动画开始到现在经过了多长时间
    uint32_t elapsed_time = millis() - charging_anim_start_time;

    // 2. 根据经过的时间，计算当前应该显示第几帧的图标
    //    elapsed_time / 150ms 会得到 0, 1, 2, 3, 4, 5...
    int frame_index = elapsed_time / CHARGING_ICON_INTERVAL;
    
    // 3. 动画总共只有5个图标，所以我们对5取模，让帧号在 0-4 之间循环
    //    (0 -> EMPTY, 1 -> LOW, 2 -> MEDIUM, 3 -> HIGH, 4 -> FULL)
    int icon_index = frame_index % 5;
    
    // 4. 根据计算出的图标索引，调用对应的绘图函数
    switch (icon_index) {
        case 0:
            strip.Draw_pic(LEVEL_EMPTY_num_1, LEVEL_EMPTY_color_1);
            break;
        case 1:
            strip.Draw_pic(LEVEL_LOW_num, LEVEL_LOW_color);
            break;
        case 2:
            strip.Draw_pic(LEVEL_MEDIUM_num, LEVEL_MEDIUM_color);
            break;
        case 3:
            strip.Draw_pic(LEVEL_HIGH_num, LEVEL_HIGH_color);
            break;
        case 4:
            strip.Draw_pic(LEVEL_FULL_num, LEVEL_FULL_color);
            break;
    }
}

void draw_brightness_icon(uint8_t level) {
    switch(level) {
        case 0: strip.Draw_pic(LEVEL_BRIGHTNESS_num_1,LEVEL_BRIGHTNESS_1); break;
        case 1: strip.Draw_pic(LEVEL_BRIGHTNESS_num_2,LEVEL_BRIGHTNESS_2); break;
        case 2: strip.Draw_pic(LEVEL_BRIGHTNESS_num_3,LEVEL_BRIGHTNESS_3); break;
        case 3: strip.Draw_pic(LEVEL_BRIGHTNESS_num_4,LEVEL_BRIGHTNESS_4); break;
        case 4: strip.Draw_pic(LEVEL_BRIGHTNESS_num_5,LEVEL_BRIGHTNESS_5); break;
    }
}

