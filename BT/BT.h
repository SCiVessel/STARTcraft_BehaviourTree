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
#include "BT_OOP/Unit/SCV/SCV_DECO_CONDITION_NOT_ENOUGH_WORKERS_FARMING_GEYSER.h"
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

	#include "BT_OOP/Unit/UNIT_ACTION_COUNTER_ATTACK.h"
	#include "BT_OOP/Unit/UNIT_DECO_CONDITION_GO_COUNTER_ATTACK.h"

	#include "BT_OOP/Unit/UNIT_ACTION_SEARCHSIDES.h"


		//SCV
		#include "BT_OOP/Unit/SCV/SCV_DECO_CONDITION_EARLY_GAME_SCOUTING.h"
		#include "BT_OOP/Unit/SCV/SCV_ACTION_SEND_IDLE_WORKER_TO_SCOUT.h"


		#include "BT_OOP/Unit/SCV/SCV_ACTION_SEND_IDLE_WORKER_TO_MINERALS.h"
		#include "BT_OOP/Unit/SCV/SCV_ACTION_SEND_IDLE_WORKER_TO_REFINERY.h"

		#include "BT_OOP/Unit/SCV/SCV_DECO_CONDITION_NOT_ENOUGH_REFINERY.h"

		#include "BT_OOP/Unit/SCV/SCV_ACTION_BUILD_SUPPLY_PROVIDER.h"
		#include "BT_OOP/Unit/SCV/SCV_ACTION_BUILD_BARRACKS.h"
		
		#include "BT_OOP/Unit/SCV/SCV_ACTION_BUILD_REFINERY.h"

		#include "BT_OOP/Unit/SCV/SCV_DECO_CONDITION_NOT_ENOUGH_ACADEMY.h"
		#include "BT_OOP/Unit/SCV/SCV_ACTION_BUILD_ACADEMY.h"

		#include "BT_OOP/Unit/SCV/SCV_DECO_CONDITION_NOT_ENOUGH_FACTORY.h"
		#include "BT_OOP/Unit/SCV/SCV_ACTION_BUILD_FACTORY.h"

		#include "BT_OOP/Unit/SCV/SCV_DECO_CONDITION_NOT_ENOUGH_STARPORT.h"
		#include "BT_OOP/Unit/SCV/SCV_ACTION_BUILD_STARPORT.h"

		#include "BT_OOP/Unit/SCV/SCV_DECO_CONDITION_NOT_ENOUGH_SCIENCEFACILITY.h"
		#include "BT_OOP/Unit/SCV/SCV_ACTION_BUILD_SCIENCEFACILITY.h"
		
		#include "BT_OOP/Unit/SCV/SCV_DECO_CONDITION_NOT_ENOUGH_ENGINEERINGBAY.h"
		#include "BT_OOP/Unit/SCV/SCV_ACTION_BUILD_ENGINEERINGBAY.h"

		#include "BT_OOP/Unit/SCV/SCV_DECO_CONDITION_NOT_ENOUGH_ARMORY.h"
		#include "BT_OOP/Unit/SCV/SCV_ACTION_BUILD_ARMORY.h"

		#include "BT_OOP/Unit/SCV/SCV_DECO_CONDITION_NOT_ENOUGH_COMMANDCENTER.h"
		#include "BT_OOP/Unit/SCV/SCV_ACTION_BUILD_COMMANDCENTER.h"

		#include "BT_OOP/Unit/SCV/SCV_ACTION_BUILD_UNFINISHED_BUILDING.h"
		
		//#include "BT_OOP/Unit/SCV/SCV_ACTION_BUILD_MISSILE_TURRET.h"


	//Building Actions
		

		//Comand Center
		#include "BT_OOP/Building/CommandCenter/CC_ACTION_TRAIN_WORKER.h"

		#include"BT_OOP/Building/CommandCenter/CC_DECO_CONDITION_NOT_ENOUGH_COMSATSTATION.h"
		#include"BT_OOP/Building/CommandCenter/CC_ACTION_BUILD_COMSATSTATION.h"

		#include"BT_OOP/Building/CommandCenter/ComsatStation/CS_ACTION_USE_ABILITY_SCANNERSWEEP.h"


		//Barracks
		#include "BT_OOP/Building/Barracks/BA_DECO_CONDITION_NOT_ENOUGH_MARINE.h"
		#include "BT_OOP/Building/Barracks/BA_ACTION_TRAIN_MARINE.h"

		#include "BT_OOP/Building/Barracks/BA_DECO_CONDITION_NOT_ENOUGH_FIREBAT.h"
		#include "BT_OOP/Building/Barracks/BA_ACTION_TRAIN_FIREBAT.h"

		#include "BT_OOP/Building/Barracks/BA_DECO_CONDITION_NOT_ENOUGH_MEDIC.h"
		#include "BT_OOP/Building/Barracks/BA_ACTION_TRAIN_MEDIC.h"

		#include "BT_OOP/Building/Barracks/BA_DECO_CONDITION_NOT_ENOUGH_GHOST.h"
		#include "BT_OOP/Building/Barracks/BA_ACTION_TRAIN_GHOST.h"

		//Factory
		#include "BT_OOP/Building/Factory/FA_DECO_CONDITION_NOT_ENOUGH_MACHINESHOP.h"
		#include "BT_OOP/Building/Factory/FA_ACTION_BUILD_MACHINESHOP.h"

		#include "BT_OOP/Building/Factory/FA_DECO_CONDITION_NOT_ENOUGH_VULTURE.h"
		#include "BT_OOP/Building/Factory/FA_ACTION_TRAIN_VULTURE.h"

		#include "BT_OOP/Building/Factory/FA_DECO_CONDITION_NOT_ENOUGH_SIEGETANK.h"
		#include "BT_OOP/Building/Factory/FA_ACTION_TRAIN_SIEGETANK.h"

		#include "BT_OOP/Building/Factory/FA_DECO_CONDITION_NOT_ENOUGH_GOLIATH.h"
		#include "BT_OOP/Building/Factory/FA_ACTION_TRAIN_GOLIATH.h"

		//Starport
		#include "BT_OOP/Building/Starport/SP_DECO_CONDITION_NOT_ENOUGH_CONTROLTOWER.h"
		#include "BT_OOP/Building/Starport/SP_ACTION_BUILD_CONTROLTOWER.h"

		#include "BT_OOP/Building/Starport/SP_DECO_CONDITION_NOT_ENOUGH_WRAITH.h"
		#include "BT_OOP/Building/Starport/SP_ACTION_TRAIN_WRAITH.h"

		#include "BT_OOP/Building/Starport/SP_DECO_CONDITION_NOT_ENOUGH_DROPSHIP.h"
		#include "BT_OOP/Building/Starport/SP_ACTION_TRAIN_DROPSHIP.h"

		#include "BT_OOP/Building/Starport/SP_DECO_CONDITION_NOT_ENOUGH_SCIENCEVESSEL.h"
		#include "BT_OOP/Building/Starport/SP_ACTION_TRAIN_SCIENCEVESSEL.h"

		#include "BT_OOP/Building/Starport/SP_DECO_CONDITION_NOT_ENOUGH_VALKYRIE.h"
		#include "BT_OOP/Building/Starport/SP_ACTION_TRAIN_VALKYRIE.h"

		#include "BT_OOP/Building/Starport/SP_DECO_CONDITION_NOT_ENOUGH_BATTLECRUISER.h"
		#include "BT_OOP/Building/Starport/SP_ACTION_TRAIN_BATTLECRUISER.h"

		//Science Facility
		#include "BT_OOP/Building/ScienceFacility/SF_DECO_CONDITION_NOT_ENOUGH_COVERTOPS.h"
		#include "BT_OOP/Building/ScienceFacility/SF_ACTION_BUILD_COVERTOPS.h"

		#include "BT_OOP/Building/ScienceFacility/SF_DECO_CONDITION_NOT_ENOUGH_PHYSICSLAB.h"
		#include "BT_OOP/Building/ScienceFacility/SF_ACTION_BUILD_PHYSICSLAB.h"
		
	//Global
		#include "BT_OOP/Global/GLOBAL_DECO_CONDITION_IS_UNDER_ATTACK.h"

	//Tech
		#include "BT/BT_OOP/Building/Academy/AC_ACTION_RESEARCH_CADUCEUSREACTOR.h"
		#include "BT/BT_OOP/Building/Academy/AC_ACTION_RESEARCH_OPTICFLARE.h"
		#include "BT/BT_OOP/Building/Academy/AC_ACTION_RESEARCH_RESTORATION.h"
		#include "BT/BT_OOP/Building/Academy/AC_ACTION_RESEARCH_STIMPACKTECH.h"
		#include "BT/BT_OOP/Building/Academy/AC_ACTION_RESEARCH_U238SHELLS.h"
		#include "BT/BT_OOP/Building/Academy/AC_DECO_CONDITION_RESEARCH_CADUCEUSREACTOR.h"
		#include "BT/BT_OOP/Building/Academy/AC_DECO_CONDITION_RESEARCH_OPTICFLARE.h"
		#include "BT/BT_OOP/Building/Academy/AC_DECO_CONDITION_RESEARCH_RESTORATION.h"
		#include "BT/BT_OOP/Building/Academy/AC_DECO_CONDITION_RESEARCH_STIMPACKTECH.h"
		#include "BT/BT_OOP/Building/Academy/AC_DECO_CONDITION_RESEARCH_U238SHELLS.h"

		#include "BT/BT_OOP/Building/Armory/AR_ACTION_UPGRADE_SHIPARMOR_LV1.h"
		#include "BT/BT_OOP/Building/Armory/AR_ACTION_UPGRADE_SHIPARMOR_LV2.h"
		#include "BT/BT_OOP/Building/Armory/AR_ACTION_UPGRADE_SHIPARMOR_LV3.h"
		#include "BT/BT_OOP/Building/Armory/AR_ACTION_UPGRADE_SHIPWEAPONS_LV1.h"
		#include "BT/BT_OOP/Building/Armory/AR_ACTION_UPGRADE_SHIPWEAPONS_LV2.h"
		#include "BT/BT_OOP/Building/Armory/AR_ACTION_UPGRADE_SHIPWEAPONS_LV3.h"
		#include "BT/BT_OOP/Building/Armory/AR_ACTION_UPGRADE_VEHICLEARMOR_LV1.h"
		#include "BT/BT_OOP/Building/Armory/AR_ACTION_UPGRADE_VEHICLEARMOR_LV2.h"
		#include "BT/BT_OOP/Building/Armory/AR_ACTION_UPGRADE_VEHICLEARMOR_LV3.h"
		#include "BT/BT_OOP/Building/Armory/AR_ACTION_UPGRADE_VEHICLEWEAPONS_LV1.h"
		#include "BT/BT_OOP/Building/Armory/AR_ACTION_UPGRADE_VEHICLEWEAPONS_LV2.h"
		#include "BT/BT_OOP/Building/Armory/AR_ACTION_UPGRADE_VEHICLEWEAPONS_LV3.h"
		#include "BT/BT_OOP/Building/Armory/AR_DECO_CONDITION_UPGRADE_SHIPARMOR_LV1.h"
		#include "BT/BT_OOP/Building/Armory/AR_DECO_CONDITION_UPGRADE_SHIPARMOR_LV2.h"
		#include "BT/BT_OOP/Building/Armory/AR_DECO_CONDITION_UPGRADE_SHIPARMOR_LV3.h"
		#include "BT/BT_OOP/Building/Armory/AR_DECO_CONDITION_UPGRADE_SHIPWEAPONS_LV1.h"
		#include "BT/BT_OOP/Building/Armory/AR_DECO_CONDITION_UPGRADE_SHIPWEAPONS_LV2.h"
		#include "BT/BT_OOP/Building/Armory/AR_DECO_CONDITION_UPGRADE_SHIPWEAPONS_LV3.h"
		#include "BT/BT_OOP/Building/Armory/AR_DECO_CONDITION_UPGRADE_VEHICLEARMOR_LV1.h"
		#include "BT/BT_OOP/Building/Armory/AR_DECO_CONDITION_UPGRADE_VEHICLEARMOR_LV2.h"
		#include "BT/BT_OOP/Building/Armory/AR_DECO_CONDITION_UPGRADE_VEHICLEARMOR_LV3.h"
		#include "BT/BT_OOP/Building/Armory/AR_DECO_CONDITION_UPGRADE_VEHICLEWEAPONS_LV1.h"
		#include "BT/BT_OOP/Building/Armory/AR_DECO_CONDITION_UPGRADE_VEHICLEWEAPONS_LV2.h"
		#include "BT/BT_OOP/Building/Armory/AR_DECO_CONDITION_UPGRADE_VEHICLEWEAPONS_LV3.h"

		#include "BT/BT_OOP/Building/EngineeringBay/EB_ACTION_UPGRADE_INFANTRYARMOR_LV1.h"
		#include "BT/BT_OOP/Building/EngineeringBay/EB_ACTION_UPGRADE_INFANTRYARMOR_LV2.h"
		#include "BT/BT_OOP/Building/EngineeringBay/EB_ACTION_UPGRADE_INFANTRYARMOR_LV3.h"
		#include "BT/BT_OOP/Building/EngineeringBay/EB_ACTION_UPGRADE_INFANTRYWEAPONS_LV1.h"
		#include "BT/BT_OOP/Building/EngineeringBay/EB_ACTION_UPGRADE_INFANTRYWEAPONS_LV2.h"
		#include "BT/BT_OOP/Building/EngineeringBay/EB_ACTION_UPGRADE_INFANTRYWEAPONS_LV3.h"
		#include "BT/BT_OOP/Building/EngineeringBay/EB_DECO_CONDITION_UPGRADE_INFANTRYARMOR_LV1.h"
		#include "BT/BT_OOP/Building/EngineeringBay/EB_DECO_CONDITION_UPGRADE_INFANTRYARMOR_LV2.h"
		#include "BT/BT_OOP/Building/EngineeringBay/EB_DECO_CONDITION_UPGRADE_INFANTRYARMOR_LV3.h"
		#include "BT/BT_OOP/Building/EngineeringBay/EB_DECO_CONDITION_UPGRADE_INFANTRYWEAPONS_LV1.h"
		#include "BT/BT_OOP/Building/EngineeringBay/EB_DECO_CONDITION_UPGRADE_INFANTRYWEAPONS_LV2.h"
		#include "BT/BT_OOP/Building/EngineeringBay/EB_DECO_CONDITION_UPGRADE_INFANTRYWEAPONS_LV3.h"

		#include "BT/BT_OOP/Building/Factory/MachineShop/MS_ACTION_RESEARCH_CHARONBOOSTERS.h"
		#include "BT/BT_OOP/Building/Factory/MachineShop/MS_ACTION_RESEARCH_IONTHRUSTERS.h"
		#include "BT/BT_OOP/Building/Factory/MachineShop/MS_ACTION_RESEARCH_SIEGETECH.h"
		#include "BT/BT_OOP/Building/Factory/MachineShop/MS_ACTION_RESEARCH_SPIDERMINE.h"
		#include "BT/BT_OOP/Building/Factory/MachineShop/MS_DECO_CONDITION_RESEARCH_CHARONBOOSTERS.h"
		#include "BT/BT_OOP/Building/Factory/MachineShop/MS_DECO_CONDITION_RESEARCH_IONTHRUSTERS.h"
		#include "BT/BT_OOP/Building/Factory/MachineShop/MS_DECO_CONDITION_RESEARCH_SIEGETECH.h"
		#include "BT/BT_OOP/Building/Factory/MachineShop/MS_DECO_CONDITION_RESEARCH_SPIDERMINE.h"

		#include "BT/BT_OOP/Building/ScienceFacility/SF_ACTION_RESEARCH_EMPSHOCKWAVE.h"
		#include "BT/BT_OOP/Building/ScienceFacility/SF_ACTION_RESEARCH_IRRADIATE.h"
		#include "BT/BT_OOP/Building/ScienceFacility/SF_ACTION_RESEARCH_TITANREACTOR.h"
		#include "BT/BT_OOP/Building/ScienceFacility/SF_DECO_CONDITION_RESEARCH_EMPSHOCKWAVE.h"
		#include "BT/BT_OOP/Building/ScienceFacility/SF_DECO_CONDITION_RESEARCH_IRRADIATE.h"
		#include "BT/BT_OOP/Building/ScienceFacility/SF_DECO_CONDITION_RESEARCH_TITANREACTOR.h"

		#include "BT/BT_OOP/Building/ScienceFacility/CovertOps/CO_ACTION_RESEARCH_LOCKDOWN.h"
		#include "BT/BT_OOP/Building/ScienceFacility/CovertOps/CO_ACTION_RESEARCH_MOEBIUSREACTOR.h"
		#include "BT/BT_OOP/Building/ScienceFacility/CovertOps/CO_ACTION_RESEARCH_OCULARIMPLANTS.h"
		#include "BT/BT_OOP/Building/ScienceFacility/CovertOps/CO_ACTION_RESEARCH_PERSONALCLOAKING.h"
		#include "BT/BT_OOP/Building/ScienceFacility/CovertOps/CO_DECO_CONDITION_RESEARCH_LOCKDOWN.h"
		#include "BT/BT_OOP/Building/ScienceFacility/CovertOps/CO_DECO_CONDITION_RESEARCH_MOEBIUSREACTOR.h"
		#include "BT/BT_OOP/Building/ScienceFacility/CovertOps/CO_DECO_CONDITION_RESEARCH_OCULARIMPLANTS.h"
		#include "BT/BT_OOP/Building/ScienceFacility/CovertOps/CO_DECO_CONDITION_RESEARCH_PERSONALCLOAKING.h"

		#include "BT/BT_OOP/Building/ScienceFacility/PhysicsLab/PL_ACTION_RESEARCH_COLOSSUSREACTOR.h"
		#include "BT/BT_OOP/Building/ScienceFacility/PhysicsLab/PL_ACTION_RESEARCH_YAMATOGUN.h"
		#include "BT/BT_OOP/Building/ScienceFacility/PhysicsLab/PL_DECO_CONDITION_RESEARCH_COLOSSUSREACTOR.h"
		#include "BT/BT_OOP/Building/ScienceFacility/PhysicsLab/PL_DECO_CONDITION_RESEARCH_YAMATOGUN.h"

		#include "BT/BT_OOP/Building/Starport/ControlTower/CT_ACTION_RESEARCH_APOLLOREACTOR.h"
		#include "BT/BT_OOP/Building/Starport/ControlTower/CT_ACTION_RESEARCH_CLOAKINGFIELD.h"
		#include "BT/BT_OOP/Building/Starport/ControlTower/CT_DECO_CONDITION_RESEARCH_APOLLOREACTOR.h"
		#include "BT/BT_OOP/Building/Starport/ControlTower/CT_DECO_CONDITION_RESEARCH_CLOAKINGFIELD.h"

		//Skill
		#include "BT/BT_OOP/Unit/Battlecruiser/BC_ACTION_USE_ABILITY_YAMATOGUN.h"

		#include "BT/BT_OOP/Unit/Dropship/DS_ACTION_USE_ABILITY_LOAD.h"
		#include "BT/BT_OOP/Unit/Dropship/DS_ACTION_USE_ABILITY_UNLOAD.h"

		#include "BT/BT_OOP/Unit/Firebat/FB_ACTION_USE_ABILITY_STIMPACK.h"

		#include "BT/BT_OOP/Unit/Ghost/GH_ACTION_USE_ABILITY_CLOAK.h"
		#include "BT/BT_OOP/Unit/Ghost/GH_ACTION_USE_ABILITY_LOCKDOWN.h"
		#include "BT/BT_OOP/Unit/Ghost/GH_ACTION_USE_ABILITY_NUKE.h"
		#include "BT/BT_OOP/Unit/Ghost/GH_ACTION_USE_ABILITY_UNCLOAK.h"

		#include "BT/BT_OOP/Unit/Marine/MR_ACTION_USE_ABILITY_STIMPACK.h"

		#include "BT/BT_OOP/Unit/Medic/MD_ACTION_USE_ABILITY_HEAL.h"
		#include "BT/BT_OOP/Unit/Medic/MD_ACTION_USE_ABILITY_OPTICFLARE.h"
		#include "BT/BT_OOP/Unit/Medic/MD_ACTION_USE_ABILITY_RESTORATION.h"

		#include "BT/BT_OOP/Unit/ScienceVessel/SV_ACTION_USE_ABILITY_DEFENSIVEMATRIX.h"
		#include "BT/BT_OOP/Unit/ScienceVessel/SV_ACTION_USE_ABILITY_EMPSHOCKWAVE.h"
		#include "BT/BT_OOP/Unit/ScienceVessel/SV_ACTION_USE_ABILITY_IRRADIATE.h"

		#include "BT/BT_OOP/Unit/SCV/SCV_ACTION_REPAIR.h"

		#include "BT/BT_OOP/Unit/SiegeTank/ST_ACTION_USE_ABILITY_SIEGEMODE.h"
		#include "BT/BT_OOP/Unit/SiegeTank/ST_ACTION_USE_ABILITY_TANKMODE.h"

		#include "BT/BT_OOP/Unit/Vulture/VT_ACTION_USE_ABILITY_SPIDERMINE.h"

		#include "BT/BT_OOP/Unit/Wraith/WR_ACTION_USE_ABILITY_CLOAK.h"
		#include "BT/BT_OOP/Unit/Wraith/WR_ACTION_USE_ABILITY_UNCLOAK.h"
