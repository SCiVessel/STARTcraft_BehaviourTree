#include "BA_DECO_CONDITION_NOT_ENOUGH_MARINE.h"
#include "Data.h"
#include <BWAPI.h>
#include "Tools.h"

BA_DECO_CONDITION_NOT_ENOUGH_MARINE::BA_DECO_CONDITION_NOT_ENOUGH_MARINE(std::string name, BT_NODE* parent)
    : BT_DECO_CONDITION(name,parent, IsThereNotEnoughMarine) {}


std::string BA_DECO_CONDITION_NOT_ENOUGH_MARINE::GetDescription()
{
    return "DECO_CONDITION_NOT_ENOUGH_MARINE";
}

bool BA_DECO_CONDITION_NOT_ENOUGH_MARINE::IsThereNotEnoughMarine(void *data)
{
    Data* pData = (Data*)data;
    
    // Do nothing if we have NOT ENOUGH MINERALS
    if (BWAPI::Broodwar->self()->minerals() < 50)
    {
        return false;
    }

    return true;
}
