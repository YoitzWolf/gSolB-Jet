#ifndef UActionInitialization_h
#define UActionInitialization_h 1

#include "UActionInitialization.hpp"
#include "UPrimaryGeneratorAction.hpp"
#include "URunAction.hpp"

void UActionInitialisation::Build() const
{
	UPrimaryGeneratorAction* primary = new UPrimaryGeneratorAction();
	SetUserAction(primary);

	URunAction* runAction = new URunAction();
	SetUserAction(runAction);
}
#endif