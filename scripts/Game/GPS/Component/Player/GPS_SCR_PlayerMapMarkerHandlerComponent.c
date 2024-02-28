[EntityEditorProps(category: "GameScripted/Gps", description: "Handles GPS on map.")]
class GPS_SCR_PlayerGPSHandlerComponentClass : ScriptComponentClass{};
class GPS_SCR_PlayerGPSHandlerComponent : ScriptComponent
{
	protected Widget m_GpsWidget;

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

		SCR_MapEntity m_mapEntity = SCR_MapEntity.GetMapInstance();

		m_mapEntity.GetOnMapOpen().Insert(OnPlayerMapOpen);
		m_mapEntity.GetOnMapClose().Insert(OnPlayerMapClose);
	}

	protected void OnPlayerMapOpen(MapConfiguration config)
	{
		IEntity playerEnt = GetGame().GetPlayerController().GetControlledEntity();
		
		if (!playerEnt)  { Print("playerEnt not found"); return; }
		
		int gridX, gridZ;
		vector playerPos = playerEnt.GetOrigin();
		SCR_MapEntity.GetGridPos(playerPos, gridX: gridX, gridZ: gridZ, resMin: 2, resMax: 4);

		string sGridX = NormalizeToGridFormat(gridX.ToString());
		string sGridZ = NormalizeToGridFormat(gridZ.ToString());

		// add GPS layout
		if (!m_GpsWidget) {
			Widget root = m_mapEntity.GetMapMenuRoot();
			m_GpsWidget = root.GetWorkspace().CreateWidgets("{AD937E444AC11A45}UI/Layouts/GPS.layout");	
			Print("created m_GpsWidget "+m_GpsWidget);
		}
		
		m_GpsWidget.SetVisible(true);
		TextWidget txtWgt = TextWidget.Cast(m_GpsWidget.FindAnyWidget("Text"));
		if (!txtWgt) { Print("txtWgt not found"); return; }
		
		txtWgt.SetText(sGridX+sGridZ);
	}
	
	protected void OnPlayerMapClose(MapConfiguration config)
	{
		m_GpsWidget.SetVisible(false);
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
}
