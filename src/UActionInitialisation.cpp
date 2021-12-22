#ifndef UActionInitialization_h
#define UActionInitialization_h 1

#include "UActionInitialization.h"
#include "UPrimaryGeneratorAction.h"
#include "URunAction.h"

void UActionInitialisation::Build() const
{
	UPrimaryGeneratorAction* primary = new UPrimaryGeneratorAction();
	SetUserAction(primary);

	URunAction* runAction = new URunAction();
	SetUserAction(runAction);
}
#endif