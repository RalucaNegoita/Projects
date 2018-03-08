package games.stendhal.server.maps.ados.rosshouse;

import static org.junit.Assert.*;
import static utilities.SpeakerNPCTestHelper.getReply;

import org.junit.BeforeClass;
import org.junit.Test;

import games.stendhal.server.entity.npc.NPCList;
import games.stendhal.server.entity.npc.SpeakerNPC;
import games.stendhal.server.entity.npc.fsm.Engine;
import games.stendhal.server.entity.player.Player;
import utilities.PlayerTestHelper;
import utilities.QuestHelper;
import utilities.ZonePlayerAndNPCTestImpl;

public class FatherNPCTest extends ZonePlayerAndNPCTestImpl {
	
	private static final String ZONE_NAME = "int_ados_ross_house";

	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
		QuestHelper.setUpBeforeClass();

		setupZone(ZONE_NAME);
	}//set up before class
		

	public void checkFatherNPCexists() throws Exception {
		assertNotNull(NPCList.get().get("Mr Ross"));
	}//check
	

	public FatherNPCTest() {
		setNpcNames("Mr Ross");
		setZoneForPlayer(ZONE_NAME);
		addZoneConfigurator(new FatherNPC(), ZONE_NAME);
	}
    
	// Test for dialogue
	@Test
	public void testDialogue() {
	
		SpeakerNPC MrRoss = NPCList.get().get("Mr Ross");
		Engine en = MrRoss.getEngine();
		
		Player player = PlayerTestHelper.createPlayer("player");
		
	    en.step(player, "Hi");
	    
	    assertTrue(MrRoss.isTalking());
	    
	    assertEquals("Hi there.", getReply(MrRoss));
	    
	    en.step(player, "Occupation");
	    assertEquals("I'm looking after my daughter Susi.",getReply(MrRoss));
	    
	    en.step(player, "Help");
	    assertEquals("If you need help finding any buildings in Ados, the guard Julius will give you a map. He is by the city entrance.",getReply(MrRoss));
	    
	    
	    en.step(player,"Offer");
	    assertEquals( "Sorry I do not have anything to offer you, but there are two places to eat in Ados - the tavern and a bar.", getReply(MrRoss));
	    
	    
	    en.step(player, "Quest");
	    assertEquals("Oh, the teddy is upstairs on the table. Feel free to go and get it.", getReply(MrRoss));
	    
	    en.step(player, "Bye");
	    assertEquals("Bye, nice to meet you.",getReply(MrRoss));
	    
	    
	    
	    	
	}//test dialogue
	

}//fatherNPC class

