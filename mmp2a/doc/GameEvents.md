StartGameEvent(); 	//Add to GUIButtonComponent

ExitGameEvent(); 	//Add to GUIButtonComponent

MenuNavigationEvent(GameEvents ev) 	//Navigationoptions available in GUI, 
					//created when GUISteeringComp is added(MoveUp = NavigateUp, MoveDown, SwitchState = Confirm)

UpdateShipStatsEvent(ShipComponent * cmp)	//Event to Update GUI with the Stats of the Ship

UpdatePlayerStatsEvent(int resources)	//Event to Update GUI with the Playerstats

UpdateButtonMapEvent(vector<String> buttonMap)	//Event to Update buttonmap in GUI
						//idx of vector == corresponding button

TogglePopupEvent()	//sets Popupwindow visible/hidden

GameplayStateChangeEvent(IGameplayState * prev, IGameplayState * next)	//when fired switches to GameplaytransitionState
									//prev and next are set active if player confirms/declines

UpdatePopupEvent(string text)	//updates Text of popup

GameplayEndTurn()	//Ends Turn of current player, handeld in GameplayEndTurnState
										