#pragma once
//#define BT_DEBUG_VERBOSE
 
#include "BT_NODE.h"
#include "BT_LEAF.h"
#include "BT_ACTION.h"
#include "BT_DECORATOR.h"

//Composite notes
#include "BT_SEQUENCER.h"
#include "BT_SELECTOR.h"
#include "BT_PARALLEL_SEQUENCER.h"
#include "BT_PARALLEL_SELECTOR.h"

//Decorators
#include "BT_DECO_CONDITION.h"
#include "BT_DECO_COND_GREATER_THAN.h"
#include "BT_DECO_COND_LESSER_THAN.h"

#include "BT_DECO_INVERTER.h"
#include "BT_DECO_REPEATER.h"
#include "BT_DECO_RETURN_FAILURE.h"
#include "BT_DECO_RETURN_SUCCESS.h"
#include "BT_DECO_UNTIL_FAILURE.h"
#include "BT_DECO_UNTIL_SUCCESS.h"

// Conditions
#include "BT_CONDITION.h"
#include "BT_COND_GREATER_THAN.h"
#include "BT_COND_LESSER_THAN.h"

///Decorator Conditions
#include "BT_OOP/Global/BT_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_MINERALS.h"
#include "BT_OOP/Global/BT_DECO_CONDITION_NOT_ENOUGH_WORKERS.h"
#include "BT_OOP/Global/BT_DECO_CONDITION_NOT_ENOUGH_SUPPLY.h"
#include "BT_OOP/Global/BT_DECO_CONDITION_NOT_ENOUGH_BARRACKS.h"

///Actions
#include "BT_ACTION_IDLE.h"
#include "BT_ACTION_WAIT.h"
#include "BT_ACTION_LOG.h"

	//Unit Actions

	#include "BT_OOP/Unit/UNIT_ACTION_RETRIBUTIVE_ATTACK.h"

		//SCV
		#include "BT_OOP/Unit/SCV/SCV_ACTION_SEND_IDLE_WORKER_TO_MINERALS.h"

		#include "BT_OOP/Unit/SCV/SCV_ACTION_BUILD_SUPPLY_PROVIDER.h"
		#include "BT_OOP/Unit/SCV/SCV_ACTION_BUILD_BARRACKS.h"


		
		//#include "BT_OOP/Unit/SCV/SCV_ACTION_BUILD_MISSILE_TURRET.h"


	//Building Actions
		

		//Comand Center
		#include "BT_OOP/Building/CommandCenter/CC_ACTION_TRAIN_WORKER.h"

		//Barracks
		#include "BT_OOP/Building/Barracks/BA_DECO_CONDITION_NOT_ENOUGH_MARINE.h"
		#include "BT_OOP/Building/Barracks/BA_ACTION_TRAIN_MARINE.h"
		
	//Global
		#include "BT_OOP/Global/GLOBAL_DECO_CONDITION_IS_UNDER_ATTACK.h"

