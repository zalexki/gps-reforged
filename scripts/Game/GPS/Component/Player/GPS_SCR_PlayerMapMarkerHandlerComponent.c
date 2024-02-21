[EntityEditorProps(category: "GameScripted/Gps", description: "Handles GPS on map.")]
class GPS_SCR_PlayerGPSHandlerComponentClass : ScriptComponentClass{};
class GPS_SCR_PlayerGPSHandlerComponent : ScriptComponent
{
	protected SCR_PlayerController m_playerController;
	protected SCR_MapEntity m_mapEntity;

	void ~GPS_SCR_PlayerGPSHandlerComponent()
	{
		m_mapEntity.GetOnMapOpen().Remove(OnPlayerMapOpen);
		m_mapEntity.GetOnMapClose().Remove(OnPlayerMapClose);
	}

	override void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);
		SetEventMask(owner, EntityEvent.INIT);
		owner.SetFlags(EntityFlags.ACTIVE, true);

		m_mapEntity = SCR_MapEntity.GetMapInstance();

		m_mapEntity.GetOnMapOpen().Insert(OnPlayerMapOpen);
		m_mapEntity.GetOnMapClose().Insert(OnPlayerMapClose);
	}

	protected void OnPlayerMapOpen(MapConfiguration config)
	{
		IEntity playerEnt = GetGame().GetPlayerController().GetControlledEntity();
		
		if (!playerEnt)
			return;
		
		int gridX, gridZ;
		vector playerPos = playerEnt.GetOrigin();
		SCR_MapEntity.GetGridPos(playerPos, gridX: gridX, gridZ: gridZ, resMin: 2, resMax: 4);
		//string label = SCR_MapEntity.GetGridLabel(playerPos, resMin: 2, resMax: 5, delimiter: ".");
		Print("playerPos "+ playerPos);
		Print("gridX "+ gridX);
		Print("gridZ "+ gridZ);
		//Print("GetGridLabel "+ label);
		string sGridX = NormalizeToGridFormat(gridX.ToString());
		string sGridZ = NormalizeToGridFormat(gridZ.ToString());
		
		Print("sGridX "+ sGridX);
		Print("sGridZ "+ sGridZ);
		
		
		// add GPS layout 
	}
	
	private string NormalizeToGridFormat(string grid)
	{
		switch (grid.Length())
		{
			case 1:
				return "00"+grid;
			case 2:
				return "0"+grid;
			default:
				return grid;
		}
		
		return grid;
	}
	
	protected void OnPlayerMapClose(MapConfiguration config)
	{
		// remove GPS layout 
	}
}
