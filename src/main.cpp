/*!
   \file main.c
   \brief Ponto de entrada do programa escrito para Arduino
   \author Arthur de Araújo Farias
   \date 07/11/2015
*/
#include <avr/pgmspace.h>

#include "../lib/main.h"

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "../lib/lcdmenu.h"
#include "../lib/nbtasks.h"
#include "../lib/keypad.h"
#include "../lib/countdown.h"
#include "../lib/CFW10.h"

/*!
   \brief Comportamento associado ao item do menu associado a inicialização e pausa do sistema
*/
void startstop_act(void);
void startstop_callback_act(void);

nbtask startstop = { "STARTSTOPLOCK", startstop_act }; /*!< Criação da tarefa associada a execução do experimento. */
nbtask startstop_break_callback = { "STARTSTOP_CALLBACK", startstop_callback_act }; /*!< Criação da tarefa associada ao fim da execução do experimento. */

extern MenuNode node01, node02;

MenuNode root = { (char *) "T. Func.", (char *) NULL, NULL, &node01, NULL, NULL, { ._int = 0 }, { ._int = 60 }, { ._int = 0 }, MENU_NODE_VALUE_TYPE_INTEGER, (char *) "Min", (char *) NULL, NULL }; /*!< Definição do elemento raiz do menu, este item do menu configurará o tempo em que o experimento funcionará */
MenuNode node01 = { (char *) "Vel.", (char *) NULL, &root, &node02, NULL, NULL, { ._int = 0 }, { ._int = 1250 } , { ._int = 0 }, MENU_NODE_VALUE_TYPE_INTEGER, (char *) "RPM", (char *) NULL, NULL }; /*!< Este item do menu configurará o número de rotações por minuto que a máquina executará. */
MenuNode node02 = { (char *) "Iniciar", (char *) "Parar", &node01, NULL, NULL, NULL, { ._bool = 0 }, 0, 0, MENU_NODE_VALUE_TYPE_BOOLEAN, (char *) NULL, startstop, NULL }; /*!< Este item do menu será utilizado para inicializar ou parar a execução do experimento. */

#define LCD_D4	22
#define LCD_D5	23
#define LCD_D6	24
#define LCD_D7	25
#define LCD_E		26
#define LCD_RS	27
#define LCD_RW	28

LiquidCrystal _display( LCD_RS,LCD_RW,LCD_E,LCD_D4,LCD_D5,LCD_D6,LCD_D7 ); // TODO: set display pins

/*!
   \brief Função chamada para pre-configuração do sistema
*/
void setup() {

	Serial.begin(9600);
	task_cbuff_setup();
	lcdmenu_setup();
	cfw10_setup();
	keypad_setup();

}

/*!
   \brief Função que será executada em um laço infinito
*/
void loop() {

	task_cbuff_play();

}

void startstop_act(void) {

	if (mn_current == &node02 && node02.value._bool == true) {
		mn_flag_scroll_lock = true;

		countdown_setup( root.value._int*60, &startstop_break_callback );

		cfw10_start( ( (double) node01.value._int ) / 1250.00 );

	} else {
		countdown_break(&startstop_break_callback);
		mn_flag_scroll_lock = false;
	}

}

void startstop_callback_act(void) {
	mn_flag_scroll_lock = false;
	node02.value._bool = false;
	cfw10_stop();
	task_cbuff_insert(lcdmenu_draw);
}
