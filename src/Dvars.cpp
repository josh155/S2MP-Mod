#include "pch.h"
#include "FuncPointers.h"
#include "Dvars.hpp"
#include "Console.hpp"
#include "Hook.hpp"
#include "DevDef.h"



typedef void (*Dvar_SetVariant_t)(dvar_t* dvar, DvarValue* value, int source);
static Dvar_SetVariant_t fpDvar_SetVariant;

void Dvar_SetVariant_hookfunc(dvar_t* dvar, DvarValue* value, int source) {
    if (!strcmp(dvar->name, "3078")) {
        if (source != 1) {
            return;
        }
    }
    fpDvar_SetVariant(dvar, value, source);
}

void setBoolDvar(const char* dvarName, bool value) {
    dvar_t* var = Functions::_Dvar_FindVar(dvarName);

    if (!var) {
        return;
    }

    var->current.enabled = value;
}

void setStringDvar(const char* dvarName, const char* value) {
    dvar_t* var = Functions::_Dvar_FindVar(dvarName);

    if (!var) {
        return;
    }

    var->current.string = value;
}

void setIntDvar(const char* dvarName, int value) {
    dvar_t* var = Functions::_Dvar_FindVar(dvarName);

    if (!var) {
        return;
    }

    var->current.integer = value;
}

void Dvars::initPatches() {
    //filter out specific dvars from being modified
	Hook::create("Dvar_SetVariant", 0xB20C0_b, &Dvar_SetVariant_hookfunc, &fpDvar_SetVariant);

    //TEMP solution for aim assist
    setBoolDvar("387", 1);

    //disable telemetry and dlog
    setBoolDvar("5785", 0); //dlog_active
    setStringDvar("5138", "0.0.0.0"); //dlog_devpointHost
    setIntDvar("telemetry_error_killswitch", 1);
    setIntDvar("telemetry_active", 0);
    std::strcpy((char*)0xB9D9D8_b, "nothankyou"); //replace dloguploader name

}