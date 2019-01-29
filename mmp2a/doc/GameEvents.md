StartGameEvent(); 	//Add to GUIButtonComponent
ExitGameEvent(); 	//Add to GUIButtonComponent
MenuNavigationEvent(GameEvents ev) 	//Navigationoptions available in GUI, 
					//created when GUISteeringComp is added(MoveUp = NavigateUp, MoveDown, SwitchState = Confirm)
UpdateShipStatsEvent(ShipComponent * cmp)	//Event to Update GUI with the Stats of the Ship
UpdatePlayerStatsEvent(...) 	//Event to Update GUI with the Playerstats