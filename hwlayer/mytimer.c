#include "mytimer.h"

void conf_mytimer(){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	// uruchom dany kanał
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// zapisz wypełnioną strukturę do rejestrów
	NVIC_Init(&NVIC_InitStructure);
}

void init_mytimer(){
	conf_mytimer();

	// wyczyszczenie przerwania od timera 3 (wystąpiło przy konfiguracji timera)
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	// zezwolenie na przerwania od przepełnienia dla timera 3
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);


}
void disable_mytimer(){
	TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
}

