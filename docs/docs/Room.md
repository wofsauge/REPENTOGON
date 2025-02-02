---
tags:
  - Class
---
# Class "Room"

## Modified Functions

### SpawnGridEntity () {: aria-label='Modified Functions' }
#### boolean SpawnGridEntity ( int GridIndex, [GridEntityType](https://wofsauge.github.io/IsaacDocs/rep/enums/GridEntityType.html) Type, int Variant = 0, int Seed = nil, int VarData = 0 ) {: .copyable aria-label='Modified Functions' }
#### boolean SpawnGridEntity ( int GridIndex, [GridEntityDesc](https://wofsauge.github.io/IsaacDocs/rep/GridEntityDesc.html) Descriptor) {: .copyable aria-label='Modified Functions' }

No longer crashes if an invalid `GridIndex` is used. All arguments beyond `Type` are optional. An overload has been added to allow spawning a new grid entity using an existing `GridEntityDesc`.
___

## Functions

### CanPickupGridEntity () {: aria-label='Functions' }
#### boolean CanPickupGridEntity ( int GridIndex ) {: .copyable aria-label='Functions' }
Returns true if the gridentity at the given position can be picked up.
___
### CanSpawnObstacleAtPosition () {: aria-label='Functions' }
#### boolean CanSpawnObstacleAtPosition ( int GridIndex, boolean Force ) {: .copyable aria-label='Functions' }

___
### GetBackdrop () {: aria-label='Functions' }
#### [Backdrop](Backdrop.md) GetBackdrop ( ) {: .copyable aria-label='Functions' }
Returns a [Backdrop](Backdrop.md) object.

___
### GetCamera () {: aria-label='Functions' }
#### [Camera](Camera.md) GetCamera ( ) {: .copyable aria-label='Functions' }
Returns a [Camera](Camera.md) object.

___
### GetChampionBossChance () {: aria-label='Functions' }
#### float GetChampionBossChance ( ) {: .copyable aria-label='Functions' }
Return the probability that boss spawns in this room will be champions.

___
### GetEffects () {: aria-label='Functions' }
#### [TemporaryEffects](https://wofsauge.github.io/IsaacDocs/rep/TemporaryEffects.html) GetEffects ( ) {: .copyable aria-label='Functions' }

___
### GetFloorColor () {: aria-label='Functions' }
#### [Color](Color.md) GetFloorColor ( ) {: .copyable aria-label='Functions' }

___
### GetFXParams () {: aria-label='Functions' }
#### [FXParams](FXParams.md) GetFXParams ( ) {: .copyable aria-label='Functions' }

___
### GetGreedWaveTimer () {: aria-label='Functions' }
#### int GetGreedWaveTimer ( ) {: .copyable aria-label='Functions' }

___
### GetGridIndexByTile () {: aria-label='Functions' }
#### int GetGridIndexByTile ( int GridRow, int GridColumn ) {: .copyable aria-label='Functions' }

___
### GetRail () {: aria-label='Functions' }
#### [StbRailVariant](enums/StbRailVariant.md) GetRail ( int GridIndex ) {: .copyable aria-label='Functions' }

___
### GetRailManager () {: aria-label='Functions' }
#### [RailManager](RailManager.md) GetRailManager ( ) {: .copyable aria-label='Functions' }

___
### GetRoomClearDelay () {: aria-label='Functions' }
#### int GetRoomClearDelay ( ) {: .copyable aria-label='Functions' }

___
### GetShopItemPrice () {: aria-label='Functions' }
#### int GetShopItemPrice ( int EntityVariant, int EntitySubType, int ShopItemID ) {: .copyable aria-label='Functions' }
Returns the price of the item.

___
### GetWaterAmount () {: aria-label='Functions' }
#### float GetWaterAmount ( ) {: .copyable aria-label='Functions' }
Returns the "amount" of water currently in the room. Generally this will be `0` for no water and `1` for water, but values in between `0` and `1` (and technically above `1` in modded scenarios) are possible.

___
### GetWaterColor () {: aria-label='Functions' }
#### [KColor](https://wofsauge.github.io/IsaacDocs/rep/KColor.html) GetWaterColor ( ) {: .copyable aria-label='Functions' }

___
### GetWaterColorMultiplier () {: aria-label='Functions' }
#### [KColor](https://wofsauge.github.io/IsaacDocs/rep/KColor.html) GetWaterColorMultiplier ( ) {: .copyable aria-label='Functions' }

___
### IsChampionBossSeed () {: aria-label='Functions' }
#### boolean IsChampionBossSeed ( ) {: .copyable aria-label='Functions' }
Return whether boss spawns in this room will be champions.

___
### IsPersistentRoomEntity () {: aria-label='Functions' }
#### boolean IsPersistentRoomEntity ( [EntityType](https://wofsauge.github.io/IsaacDocs/rep/enums/EntityType.html) Type, int Variant = 0 ) {: .copyable aria-label='Functions' }

___
### PickupGridEntity () {: aria-label='Functions' }
#### [EntityEffect](https://wofsauge.github.io/IsaacDocs/rep/EntityEffect.html) PickupGridEntity ( int GridIndex ) {: .copyable aria-label='Functions' }

___
### RemoveGridEntityImmediate () {: aria-label='Functions' }
#### void RemoveGridEntityImmediate ( int GridIndex, int PathTrail, boolean KeepDecoration ) {: .copyable aria-label='Functions' }
*Immediately* removes the GridEntity at the given index. This means grids can be properly removed and immediately replaced, *without* the need to call Room:Update.

___
### SetBackdropType () {: aria-label='Functions' }
#### void SetBackdropType ( [BackdropType](https://wofsauge.github.io/IsaacDocs/rep/enums/BackdropType.html), int Unknown ) {: .copyable aria-label='Functions' }
This function will not work if the Unknown integer is passed as `0`.

The backdrop variant chosen is seeded based on the room, and does not persist when leaving and re-entering. Calling this function again on re-entry will result in the same backdrop variant as before.

___
### SetGreedWaveTimer () {: aria-label='Functions' }
#### void SetGreedWaveTimer ( int Time ) {: .copyable aria-label='Functions' }

___
### SetPauseTimer () {: aria-label='Functions' }
#### void SetPauseTimer ( int Duration ) {: .copyable aria-label='Functions' }

___
### SetRail () {: aria-label='Functions' }
#### void SetRail ( int GridIndex, [StbRailVariant](enums/StbRailVariant.md) RailVariant ) {: .copyable aria-label='Functions' }

___
### SetRoomClearDelay () {: aria-label='Functions' }
#### void SetRoomClearDelay ( int Delay ) {: .copyable aria-label='Functions' }

___
### SetWaterAmount () {: aria-label='Functions' }
#### void SetWaterAmount ( float Amount ) {: .copyable aria-label='Functions' }
Sets the amount of water that should be in the current room. Vanilla typically uses `0` for no water and `1` for water. You can technically go higher than this for some interesting results.

___
### SetWaterColor () {: aria-label='Functions' }
#### void SetWaterColor ( [KColor](Color.md) WaterColor ) {: .copyable aria-label='Functions' }

___
### SetWaterColorMultiplier () {: aria-label='Functions' }
#### void SetWaterColorMultiplier ( [KColor](Color.md) WaterColor ) {: .copyable aria-label='Functions' }

___
### SetWaterCurrent () {: aria-label='Functions' }
#### void SetWaterCurrent ( [Vector](Vector.md) WaterCurrent ) {: .copyable aria-label='Functions' }
Sets the strength of the water current in the room. Current sounds and particles are automatically handled.

The game typically uses `1` or `-1` for its values depending on current strength and direction. You can technically go higher than this for some interesting results. Arbitrary directions are fully supported as well.

`Vector(0, 0)` will remove the current.
___
### TryGetShopDiscount () {: aria-label='Functions' }
#### int TryGetShopDiscount ( int ShopItemIdx, int Price ) {: .copyable aria-label='Functions' }

___
### UpdateColorModifier () {: aria-label='Functions' }
#### void UpdateColorModifier ( boolean Process = true, boolean Lerp = true, float Rate = 0.015 ) {: .copyable aria-label='Functions' }
Updates the room's color correction with the copy of [ColorModifier](ColorModifier.md) stored in [FXParams](FXParams.md).
`Process` runs the color correction through some additional modifications for lava and the abandoned mineshaft sequence.

___
