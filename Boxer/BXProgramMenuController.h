/* 
 Boxer is copyright 2009 Alun Bestor and contributors.
 Boxer is released under the GNU General Public License 2.0. A full copy of this license can be
 found in this XCode project at Resources/English.lproj/GNU General Public License.txt, or read
 online at [http://www.gnu.org/licenses/gpl-2.0.txt].
 */


//BXProgramMenuController manages the default program popup button in the Inspector panel. It
//is responsible for populating the popup button menu with the available programs in the current
//gamebox (if any) and synchronising its selection with the default program of the gamebox.

#import <Cocoa/Cocoa.h>

@class BXSession;

@interface BXProgramMenuController : NSObject
{
	IBOutlet NSPopUpButton *programSelector;
	IBOutlet NSObjectController *sessionMediator;
}
@property (retain) NSPopUpButton *programSelector;		//The program selector popup button we populate.
@property (retain) NSObjectController *sessionMediator;	//The NIB's object-controller proxy for the current session.

//Sets the default program of the gamebox to the represented path of the selected menu item.
//Called by the program selector whenever its selected item is changed.
- (IBAction) changeDefaultProgram: (id)sender;

//Launches the represented path of the popup button's selected menu item.
//Currently unused - intended for a button to sit alongside the program popup selector.
- (IBAction) launchDefaultProgram: (id)sender;

//Shows a standard OS X open panel for choosing an executable file from Finder.
- (IBAction) showProgramChooserPanel: (id)sender;

//Synchronise the program selector's currently selected item with the default program
//of the current gamebox.
- (void) syncSelection;

//(Re)populate the menu with the contents of programMenuItems. Called automatically whenever
//the active session changes.
- (void) syncMenuItems;

//Returns a sorted array of NSMenuItems for the available programs in the gamebox.
//Used internally by syncMenuItems.
- (NSArray *) programMenuItems;

@end
