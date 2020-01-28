
#include QMK_KEYBOARD_H

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

//Tap dance enums
enum {
  SPC_ENT_SFT = 0,
  _MIN = 1,
  _EQL = 2,
  _INS = 3,
};

int cur_dance (qk_tap_dance_state_t *state);

//for the x tap dance. Put it here so it can be used in any keymap
void spc_finished (qk_tap_dance_state_t *state, void *user_data);
void spc_reset (qk_tap_dance_state_t *state, void *user_data);

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [SPC_ENT_SFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, spc_finished, spc_reset),
  [_MIN] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, LSFT(KC_MINS)),
  [_EQL] = ACTION_TAP_DANCE_DOUBLE(KC_EQL, LSFT(KC_EQL)),
  [_INS] = ACTION_TAP_DANCE_DOUBLE(KC_EQL, LSFT(KC_INS)),
};

#define _QW 0
#define _FN 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | ~      | -      | =      | 6      | 7      | 8      | 9      | 0      |Page Up |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | TAB    | Q      | W      | E      | R      | T      | [      | ]      | \      | Y      | U      | I      | O      | P      |Page Dn |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | SHIFT  | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      |   4    |   5    |   6    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | SHIFT  | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | ENT/SFT|   1    |   2    |   3    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | LGUI   | ALT    | CTRL/( | SPACE  | ENT/SFT| LEFT   | DOWN   | RIGHT  | BS/SFT | SPACE  | CTRL/) | ALT    | RGUI   |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_QW] = LAYOUT_ortho_5x15(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_HOME, TD(_INS),KC_END,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PGUP,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,            KC_LBRC, KC_RBRC, KC_BSLS, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_PGDN,
  KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,            KC_GRV,  TD(_MIN),TD(_EQL),KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,            XXXXXXX, KC_UP,   KC_DEL,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, XXXXXXX,
  MO(_FN), KC_LGUI, KC_LALT, KC_LCPO, KC_SPC,  TD(SPC_ENT_SFT), KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, KC_SPC,  KC_RCPC, KC_RALT, KC_RGUI, MO(_FN)
  ),

/* NUMBERS
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        | F1     | F2     | F3     | F4     | F5     |        |        |        | F6     | F7     | F8     | F9     | F10    | Brigt+ |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | F11    | F12    |        |        |        |        |        |        |        |        |        |        | PrntSc | Brigt- |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | Play   | Vol+   | Mute   |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        | Enter  | Prev   | Vol-   | Next   | Backsp |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_FN] = LAYOUT_ortho_5x15(
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_BRIU,
  _______, KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_BRID,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, KC_MPLY, KC_VOLU, KC_MUTE, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, KC_ENT,  KC_MPRV, KC_VOLD, KC_MNXT, KC_BSPC, _______, _______, _______, _______, _______
  )
};

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

void spc_finished (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: register_code(KC_SPC); break;
    case SINGLE_HOLD: register_code(KC_LSFT); break;
    case DOUBLE_TAP: register_code(KC_ENT); break;
    case DOUBLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_SINGLE_TAP: register_code(KC_SPC); unregister_code(KC_SPC); register_code(KC_SPC);
  }
}

void spc_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_SPC); break;
    case SINGLE_HOLD: unregister_code(KC_LSFT); break;
    case DOUBLE_TAP: unregister_code(KC_ENT); break;
    case DOUBLE_HOLD: unregister_code(KC_LALT);
    case DOUBLE_SINGLE_TAP: unregister_code(KC_SPC);
  }
  xtap_state.state = 0;
}


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
