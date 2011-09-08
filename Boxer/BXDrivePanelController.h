/* 
 Boxer is copyright 2011 Alun Bestor and contributors.
 Boxer is released under the GNU General Public License 2.0. A full copy of this license can be
 found in this XCode project at Resources/English.lproj/BoxerHelp/pages/legalese.html, or read
 online at [http://www.gnu.org/licenses/gpl-2.0.txt].
 */


//BXDrivePanelController manages the Drives panel of the Inspector window.

#import <Cocoa/Cocoa.h>
#import "BXOperationDelegate.h"
#import "BXCollectionItemView.h"

@class BXDriveList;
@class BXDrive;
@interface BXDrivePanelController : NSViewController <BXOperationDelegate>
{
	IBOutlet NSSegmentedControl *driveControls;
	IBOutlet NSMenu *driveActionsMenu;
	IBOutlet BXDriveList *driveList;
    
    NSIndexSet *selectedDriveIndexes;
}

#pragma mark -
#pragma mark Properties

@property (retain, nonatomic) BXDriveList *driveList;
@property (retain, nonatomic) NSSegmentedControl *driveControls;
@property (retain, nonatomic) NSMenu *driveActionsMenu;

//The list of drives to display for the current session.
//This is pre-filtered with driveFilterPredicate.
@property (readonly, nonatomic) NSArray *drives;

//The currently-selected drives, formatted for our array controller.
@property (retain, nonatomic) NSIndexSet *selectedDriveIndexes;

//How our array controller should filter our drives.
@property (readonly, nonatomic) NSPredicate *driveFilterPredicate;

//The currently-selected drives, formatted for our personal use.
@property (readonly, nonatomic) NSArray *selectedDrives;


#pragma mark -
#pragma mark Interface Actions

- (IBAction) interactWithDriveOptions: (NSSegmentedControl *)sender;

//Reveal the selected drives each in a new Finder window.
- (IBAction) revealSelectedDrivesInFinder: (id)sender;

//Change to the first selected drive in DOS. This action is disabled if a process is running.
- (IBAction) openSelectedDrivesInDOS: (id)sender; 

//Mount/unmount the selected drives in DOS. Will call mountSelectedDrives: if all selected
//drives are unmounted, or unmountSelectedDrives: if one or more selected drives is mounted.
- (IBAction) toggleSelectedDrives: (id)sender;

//Mount the selected drives in DOS.
- (IBAction) mountSelectedDrives: (id)sender;

//Unmount the selected drives from DOS, while leaving them in the drive list.
- (IBAction) unmountSelectedDrives: (id)sender;

//Unmount the selected drives from DOS, and remove them from the drive list altogether.
- (IBAction) removeSelectedDrives: (id)sender;

//Import the selected drives into the gamebox.
- (IBAction) importSelectedDrives: (id)sender;

//Cancel the import operation for the drive represented by the sender.
- (IBAction) cancelImportForDrive: (id)sender;

//Cancel the import operations for all currently selected drives.
- (IBAction) cancelImportsForSelectedDrives: (id)sender;

//Display the mount panel.
- (IBAction) showMountPanel: (id)sender;

//Re-syncs the status and actions of the button bar, whenever
//the selection changes or drives get mounted/unmounted.
- (void) syncButtonStates;

//Called whenever a new drive is mounted, to auto-select that drive in the panel.
- (void) emulatorDriveDidMount: (NSNotification *)notification;

#pragma mark -
#pragma mark Drag-dropping

//Handle drag-dropping of files and folders to mount as drives.
- (NSDragOperation) draggingEntered: (id <NSDraggingInfo>)sender;
- (BOOL) performDragOperation: (id <NSDraggingInfo>)sender;

- (BOOL) collectionView: (NSCollectionView *)collectionView
    writeItemsAtIndexes: (NSIndexSet *)indexes
           toPasteboard: (NSPasteboard *)pasteboard;

@end


//BXDriveItem represents each drive in the list and acts
//as a view controller for its corresponding BXDriveItemView.
@interface BXDriveItem : BXCollectionItem
{
    BOOL importing;
}

//The icon to display for the drive we represent.
@property (readonly, nonatomic) NSImage *icon;

//The type description to display for our drive.
@property (readonly, nonatomic) NSString *typeDescription;

//The icon to display on the insert/eject toggle.
@property (readonly, nonatomic) NSImage *iconForToggle;

//A remapping of BXDrive -mounted (in preparation for phasing it out.)
@property (readonly, nonatomic, getter=isMounted) BOOL mounted;

//Whether this drive is currently being imported to the gamebox.
//Used to toggle the visibility of import progress fields in the drive item view.
@property (assign, nonatomic, getter=isImporting) BOOL importing;


//Progress meter fields within the drive item view.
//These will be updated programmatically throughout the import progress.
@property (readonly, nonatomic) NSProgressIndicator *progressMeter;
@property (readonly, nonatomic) NSTextField *progressMeterLabel;
@property (readonly, nonatomic) NSButton *progressMeterCancel;
@property (readonly, nonatomic) NSTextField *driveTypeLabel;
@property (readonly, nonatomic) NSButton *driveToggleButton;
@property (readonly, nonatomic) NSButton *driveRevealButton;


//Import notifications dispatched by BXDrivePanelController,
//to the drive item for the drive being imported.
- (void) driveImportWillStart: (NSNotification *)notification;
- (void) driveImportInProgress: (NSNotification *)notification;
- (void) driveImportWasCancelled: (NSNotification *)notification;
- (void) driveImportDidFinish: (NSNotification *)notification;
@end
