#include "mytimer.h"

void conf_mytimer(){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	// uruchom dany kana�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// zapisz wype�nion� struktur� do rejestr�w
	NVIC_Init(&NVIC_InitStructure);
}

void init_mytimer(){
	conf_mytimer();

	// wyczyszczenie przerwania od timera 3 (wyst�pi�o przy konfiguracji timera)
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	// zezwolenie na przerwania od przepe�nienia dla timera 3
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);


}
void disable_mytimer(){
	TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
}

