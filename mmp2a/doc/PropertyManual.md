# Property Manual

## TileMapObject

Consists of Layers in tiled;
Layers get converted into LayerRenderComponents

## LayerRenderComponent 
Name | Description | Default-value
-----|-------------|--------------
zIndex      | Optional, zIndex for rendering    | 0
layerId	    | Optional, ID to find Layer        | NULL_LAYER

## NodeGraphRenderComponent
Name | Description | Default-value
-----|-------------|--------------
zIndex	| Optional, zIndex for rendering	| 9
cols	| Optional, cols of nodeGrid	    | Number of tiles in height
rows	| Optional, rows of nodeGrid	    | Number of tiles in width
## GameObject
Properties: are not used at the moment
## CameraComponent
Name | Description | Default-value
-----|-------------|--------------
BoundObject | Optional, object the camera is bound to	                                    | m_gameObject
Zoom	    | Optional, zoom of camera	                                                    | 1
posX	    | Optional, x position on the screen (only used when no boundObject is given)   | 0
posY	    | Optional, y position on the screen (only used when no boundObject is given)   | 0

## SteeringComponent
Name | Description | Default-value
-----|-------------|--------------
PlayerIndex	| Playerindex for input	                                | 0
StartRow	| Optional, startposition of unit -> row on nodeGrid	| 0
StartCol	| Optional, startposition of unit -> col on nodeGrid	| 0

### AIControllerComponent
No Properties
### HumanControllerComponent
Name | Description | Default-value
-----|-------------|--------------
Action* (* = Index)	| Creates InputComponent for every Action 	| 0

#### AiInputComponent
No Properties
#### HumanInputComponent
No Properties

## DebugGeometryRenderComponent
Name | Description | Default-value
-----|-------------|--------------
width	| Determines shapeSize	| -
height	| shapeSize	            | -

## ShapeRenderComponent
Name | Description | Default-value
-----|-------------|--------------
zIndex  | Optional, zIndex for rendering    | 0

## SpriteRenderComponent
Name | Description | Default-value
-----|-------------|--------------
zIndex	    | Optional, zIndex for rendering	            | 0
Texture	    | Texture to load sprite from	                | assetPath
loadFromSet	| Optional, Load sprite from tileset?	        | False
posX	    | Optional, position on tileset	                | 0
posY	    | Optional, position on tileset	                | 0
sizeX	    | Size of textureArea to be loaded	            | 0
sizeY	    | Size of textureArea to be loaded	            | 0
tileSize	| Size of the tiles -> important for position	| 1

### FarmShipComponent
No Properties
### FighterShipComponent
No Properties
### MotherShipComponent
No Properties

## GUIButtonComponent:
!!!Immer in der Reihenfolge erstellen wie sie navigiert werden sollen
Name | Description | Default-value
-----|-------------|--------------
Text		| Text			            | Placeholder text
Event_		| Events sent by Button	    | none

## GUIRenderComponent:
Name | Description | Default-value
-----|-------------|--------------
Font		| Font				| REFSAN.TTF
Theme		| theme				| Black.txt

## GUILabelComponent:
Name | Description | Default-value
-----|-------------|--------------
Text		| Text				    | none
TextSize	| Schriftgröße			| trial and error :|

## GUISteeringComponent:
Name | Description | Default-value
-----|-------------|--------------
PlayerIndex	| idx				    | 0
Action_		| InputActions			| MoveUp, MoveDown

