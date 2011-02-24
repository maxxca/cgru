#pragma once

#include <time.h>

#include "../include/aftypes.h"

#include "af.h"

namespace af
{
///   Message - Afanasy communication unit.
/**   Any type of client ( Talk, Render), Anatoly and Afanasy communicate throug messages.
***   Message can have some data or not, determined on its type.
***   Messages with type greater than or equal to \c Msg::TDATA must have some data to be valid.
***   They must have non zero data pointer and data length greater than zero.
***   Messages with type less than \c Msg::TDATA must not have any data to be valid.
***   They must have NULL data poiner.
**/
class Msg : public Af
{
public:
/// Default constructor.
   Msg( int msgType = 0, int msgInt = 0);

/// Constructor from \c Af class.
   Msg( int msgType, Af * afClass );

   Msg( const char * rawData, int rawDataLen);

   ~Msg();///< Destructor.

/// To set zero (\c Msg::TNone ) message to some non data message. Return \c true on success.
   bool set( int msgType, int msgInt = 0);

/// Write \c Af class to message.
   bool set( int msgType, Af * afClass );

/// To set zero (\c Msg::TNone ) message to data message. Return \c true on success.
   bool setData( int size, char * msgData);

/// To set zero (\c Msg::TNone ) message to QString message. Return \c true on success.
   bool setString( QString & qstring);

/// To set zero (\c Msg::TNone ) message to QStringList message. Return \c true on success.
   bool setStringList( QStringList & qstringlist);

/// Get QString ( if message type is TQString ).
   bool getString( QString & qstring);

/// Get QString ( if message type is TQStringList ).
   bool getStringList( QStringList & qstringlist);

/**   IMPORTANT!
***   messages with (type < MText) MUST NOT have any data to be valid:
***   (( mdata == NULL) && ( data_len == 0)) ALWAYS !
***   messages with (type >= MText) MUST have some data to be valid:
***   (( mdata != NULL) && ( data_len > 0)) ALWAYS !
**/
   enum Type{
/*------------ NONDATA MESSAGES ----------------------*/
/// Default message with default type - zero. Only this type can be changed by \c set function.
/**/TNULL/**/,
/// Message set to this type itself, when reading.
/**/TVersionMismatch/**/,
/// Invalid message. This message type generated by constructors if wrong arguments provieded.
/**/TInvalid/**/,

/**/TConfirm/**/,                   ///< Simple answer with no data to confirm something.

/// Request messages, sizes, quantities statistics. Can be requested displayed by anatoly.
/**/TStatRequest/**/,

/**/TConfigLoad/**/,                ///< Reload config file
/**/TFarmLoad/**/,                  ///< Reload farm file


/**/TClientExitRequest/**/,         ///< Request to client to exit,
/**/TClientRestartRequest/**/,      ///< Restart client application,
/**/TClientStartRequest/**/,        ///< Start client application,
/**/TClientRebootRequest/**/,       ///< Reboot client host computer,
/**/TClientShutdownRequest/**/,     ///< Shutdown client host computer,

/*- Talk messages -*/
/**/TTalkId/**/,                    ///< Id for new Talk. Server sends it back when new Talk registered.
/**/TTalkUpdateId/**/,              ///< Update Talk with given id ( No information for updating Talk needed).
/**/TTalksListRequest/**/,          ///< Request online Talks list.
/**/TTalkDeregister/**/,            ///< Deregister talk with given id.


/*- Monitor messages -*/
/**/TMonitorId/**/,                 ///< Id for new Monitor. Server sends it back when new Talk registered.
/**/TMonitorUpdateId/**/,           ///< Update Monitor with given id ( No information for updating Monitor needed).
/**/TMonitorsListRequest/**/,       ///< Request online Monitors list.
/**/TMonitorDeregister/**/,         ///< Deregister monitor with given id.

/*- Render messages -*/
/** When Server successfully registered new Render it's send back it's id.**/
/**/TRenderId/**/,
/**/TRendersListRequest/**/,        ///< Request online Renders list message.
/**/TRenderLogRequestId/**/,        ///< Request a log of Render with given id.
/**/TRenderServicesRequestId/**/,   ///< Request a list of services of Render with given id.
/**/TRenderDeregister/**/,          ///< Deregister Render with given id.


/*- Users messages -*/
/**/TUsersListRequest/**/,          ///< Active users information.
/// Uset id. Afanasy sends it back as an answer on \c TUserIdRequest , which contains user name.
/**/TUserId/**/,
/**/TUserLogRequestId/**/,          ///< Request a log of User with given id.
/**/TUserJobsOrderRequestId/**/,    ///< Request User(id) jobs ids in server list order.


/*- Job messages -*/
/**/TJobsListRequest/**/,           ///< Request brief of jobs.
/**/TJobsListRequestUserId/**/,     ///< Request brief of jobs of user with given id.
/**/TJobLogRequestId/**/,           ///< Request a log of a job with given id.
/**/TJobErrorHostsRequestId/**/,    ///< Request a list of hosts produced tasks with errors.
/**/TJobsWeightRequest/**/,         ///< Request all jobs weight.

/// Request a job with given id. The answer is TJob. If there is no job with such id the answer is TJobRequestId.
/**/TJobRequestId/**/,
/// Request a job progress with given id. The answer is TJobProgress. If there is no job with such id the answer is TJobProgressRequestId.
/**/TJobProgressRequestId/**/,


/*---------------------------------------------------------------------------------------------------------*/
/*--------------------------------- DATA MESSAGES ---------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------*/


/**/TDATA/**/,                      ///< Some data.
/**/TTESTDATA/**/,                  ///< Test some data transfer.
/**/TQString/**/,                   ///< QString text message.
/**/TQStringList/**/,               ///< QStringList text message.

/**/TStatData/**/,                  ///< Statistics data.

/*- Client messages -*/

/*- Talk messages -*/
/// Register Talk. Send by Talk client to register. Server sends back its id \c TTalkId.
/**/TTalkRegister/**/,
/**/TTalksListRequestIds/**/,       ///< Request a list of Talks with given ids.
/**/TTalksList/**/,                 ///< Message with a list of online Talks.
/**/TTalkDistributeData/**/,        ///< Message with a list Talk's users and a text to send to them.
/**/TTalkData/**/,                  ///< Message to Talk with text.
/**/TTalkExit/**/,                  ///< Ask server to shutdown client application(s),


/*- Monitor messages -*/
/// Register Monitor. Send by Monitor client to register. Server sends back its id \c TMonitorId.
/**/TMonitorRegister/**/,
/**/TMonitorsListRequestIds/**/,    ///< Request a list of Monitors with given ids.
/**/TMonitorsList/**/,              ///< Message with a list of online Monitors.
/**/TMonitorSubscribe/**/,          ///< Subscribe monitor on some events.
/**/TMonitorUnsubscribe/**/,        ///< Unsubscribe monitor from some events.
/**/TMonitorUsersJobs/**/,          ///< Set users ids to monitor their jobs.
/**/TMonitorJobsIdsAdd/**/,         ///< Add jobs ids for monitoring.
/**/TMonitorJobsIdsSet/**/,         ///< Set jobs ids for monitoring.
/**/TMonitorJobsIdsDel/**/,         ///< Delete monitoring jobs ids.
/**/TMonitorMessage/**/,            ///< Send a message (TQString) to monitors with provieded ids (MCGeneral).
/**/TMonitorExit/**/,               ///< Ask server to shutdown client application(s),

/**/TMonitorEvents_BEGIN/**/,       ///< Events types start.

/**/TMonitorJobEvents_BEGIN/**/,    ///< Job events types start.
/**/TMonitorJobsAdd/**/,            ///< IDs of new jobs.
/**/TMonitorJobsChanged/**/,        ///< IDs of changed jobs.
/**/TMonitorJobsDel/**/,            ///< IDs of deleted jobs.
/**/TMonitorJobEvents_END/**/,      ///< Job events types end.

/**/TMonitorCommonEvents_BEGIN/**/, ///< Common events types start.
/**/TMonitorUsersAdd/**/,           ///< IDs of new users.
/**/TMonitorUsersChanged/**/,       ///< IDs of changed users.
/**/TMonitorUsersDel/**/,           ///< IDs of deleted users.
/**/TMonitorRendersAdd/**/,         ///< IDs of new renders.
/**/TMonitorRendersChanged/**/,     ///< IDs of changed renders.
/**/TMonitorRendersDel/**/,         ///< IDs of deleted renders.
/**/TMonitorMonitorsAdd/**/,        ///< IDs of new monitors.
/**/TMonitorMonitorsChanged/**/,    ///< IDs of changed monitors.
/**/TMonitorMonitorsDel/**/,        ///< IDs of deleted monitors.
/**/TMonitorTalksAdd/**/,           ///< IDs of new talks.
/**/TMonitorTalksDel/**/,           ///< IDs of deleted talks.
/**/TMonitorCommonEvents_END/**/,   ///< Common events types end.

/**/TMonitorEvents_END/**/,         ///< Events types end.


/*- Render messages -*/
/** Sent by Render on start, when it's server begin to listen post.
And when Render can't connect to Afanasy. Afanasy register new Render and send back it's id \c TRenderId. **/
/**/TRenderRegister/**/,
/**/TRenderUpdate/**/,              ///< Update Render, message contains its resources.
/**/TRendersListRequestIds/**/,     ///< Request a list of Renders with given ids.
/**/TRendersUpdateRequestIds/**/,   ///< Request a list of resources of Renders with given ids.
/**/TRendersList/**/,               ///< Message with a list of Renders.
/**/TRendersListUpdates/**/,        ///< Message with a list of resources of Renders.
/**/TRenderPriority/**/,            ///< Set Render priority,
/**/TRenderCapacity/**/,            ///< Set Render capacity,
/**/TRenderSetService/**/,          ///< Enable or disable Render service,
/**/TRenderRestoreDefaults/**/,     ///< Restore default Render settings,
/**/TRenderNIMBY/**/,               ///< Set Render NIMBY,
/**/TRenderUser/**/,                ///< Set Render user,
/**/TRenderNimby/**/,               ///< Set Render nimby,
/**/TRenderFree/**/,                ///< Set Render free,
/**/TRenderStopTask/**/,            ///< Signal from Afanasy to Render to stop task.
/**/TRenderCloseTask/**/,           ///< Signal from Afanasy to Render to close (delete) finished (stopped) task.
/**/TRenderEject/**/,               ///< Stop all tasks on Render,
/**/TRenderDelete/**/,              ///< Delete Render from afanasy server container and database,
/**/TRenderRestart/**/,             ///< Restart Render client program,
/**/TRenderStart/**/,               ///< Start Render client program,
/**/TRenderReboot/**/,              ///< Reboot Render host computer,
/**/TRenderShutdown/**/,            ///< Shutdown Render host computer,
/**/TRenderAnnotate/**/,            ///< Set Render annotation,
/**/TRenderExit/**/,                ///< Ask server to shutdown client application(s),


/*- Users messages -*/
/**/TUsersListRequestIds/**/,       ///< Request a list of Users with given ids.
/**/TUsersList/**/,                 ///< Active users information.
/**/TUserAdd/**/,                   ///< Add a permatent user.
/**/TUserDel/**/,                   ///< Remove a permatent user.
/**/TUserJobsLifeTime/**/,          ///< Set user jobs default life time.
/**/TUserHostsMask/**/,             ///< Set user hosts mask.
/**/TUserHostsMaskExclude/**/,      ///< Set user exclude hosts mask.
/**/TUserMaxRunningTasks/**/,       ///< Set user maximum running tasks number.
/**/TUserPriority/**/,              ///< Set user priority.
/**/TUserErrorsAvoidHost/**/,       ///< Set number of errors on host to avoid it.
/**/TUserErrorRetries/**/,          ///< Set number of automatic retries task with errors.
/**/TUserErrorsTaskSameHost/**/,    ///< Set number of errors for task on same host.
/**/TUserErrorsForgiveTime/**/,     ///< Set time to forgive error host.
/**/TUserIdRequest/**/,             ///< Request an id of user with given name.
/**/TUserMoveJobsUp/**/,            ///< Move jobs one position up in user jobs list.
/**/TUserMoveJobsDown/**/,          ///< Move jobs one position down in user jobs list.
/**/TUserMoveJobsTop/**/,           ///< Move jobs to top position in user jobs list.
/**/TUserMoveJobsBottom/**/,        ///< Move jobs to bottom position up in user jobs list.
/**/TUserJobsOrder/**/,             ///< Jobs ids in server list order.
/**/TUserAnnotate/**/,              ///< Set User annotation,


/*- Job messages -*/
/**/TJobRegister/**/,               ///< Register job.
/**/TJobStart/**/,                  ///< Start offline (paused) job.
/**/TJobStop/**/,                   ///< Stop job ( stop running tasks and set offline state).
/**/TJobRestart/**/,                ///< Restart job.
/**/TJobRestartErrors/**/,          ///< Restart tasks with errors.
/**/TJobResetErrorHosts/**/,        ///< Reset all job blocks error hosts.
/**/TJobPause/**/,                  ///< Pause job ( set offline state, keep running tasks running).
/**/TJobRestartPause/**/,           ///< Restart and pause job.
/**/TJobDelete/**/,                 ///< Delete a job.
/**/TJobsListRequestIds/**/,        ///< Request a list of Jobs with given ids.
/**/TJobsListRequestUsersIds/**/,   ///< Request brief of jobs od users with given ids.
/**/TJobsList/**/,                  ///< Jobs list information.
/**/TJobProgress/**/,               ///< Jobs progress.
/**/TJobHostsMask/**/,              ///< Set job hosts mask.
/**/TJobHostsMaskExclude/**/,       ///< Set job exclude hosts mask.
/**/TJobDependMask/**/,             ///< Set job depend mask.
/**/TJobDependMaskGlobal/**/,       ///< Set job global depend mask.
/**/TJobMaxRunningTasks/**/,        ///< Set job maximum running tasks number.
/**/TJobWaitTime/**/,               ///< Set job wait time.
/**/TJobLifeTime/**/,               ///< Set job life time.
/**/TJobPriority/**/,               ///< Set job priority.
/**/TJobNeedOS/**/,                 ///< Set a job os needed.
/**/TJobNeedProperties/**/,         ///< Set a job properties needed.
/**/TJobsWeight/**/,                ///< All jobs weight data.
/**/TJobCmdPost/**/,                ///< Set job post command.
/**/TJobAnnotate/**/,               ///< Set Job annotation,
/**/TJob/**/,                       ///< Job (all job data).

/**/TBlockDependMask/**/,           ///< Set block depend mask.
/**/TBlockTasksDependMask/**/,      ///< Set block tasks depend mask.
/**/TBlockTasksMaxRunTime/**/,      ///< Set block tasks maximum run time.
/**/TBlockHostsMask/**/,            ///< Set block hosts mask.
/**/TBlockHostsMaskExclude/**/,     ///< Set block exclude hosts mask.
/**/TBlockMaxRunningTasks/**/,      ///< Set block maximum running tasks number.
/**/TBlockCommand/**/,              ///< Set block command.
/**/TBlockWorkingDir/**/,           ///< Set block working directory.
/**/TBlockFiles/**/,                ///< Set block files.
/**/TBlockCmdPost/**/,              ///< Set block post command.
/**/TBlockService/**/,              ///< Set block task type.
/**/TBlockParser/**/,               ///< Set block parser type.
/**/TBlockParserCoeff/**/,          ///< Set block parser coefficient.
/**/TBlockResetErrorHosts/**/,      ///< Reset block avoid hosts.
/**/TBlockErrorsAvoidHost/**/,      ///< Set number of errors on host to avoid it.
/**/TBlockErrorRetries/**/,         ///< Set number of automatic retries task with errors.
/**/TBlockErrorsSameHost/**/,       ///< Set number of errors for the task on same host to make task to avoid host.
/**/TBlockErrorsForgiveTime/**/,    ///< Set time to forgive error host.
/**/TBlockCapacity/**/,             ///< Set block capacity.
/**/TBlockCapacityCoeffMin/**/,     ///< Set block capacity minimum coefficient.
/**/TBlockCapacityCoeffMax/**/,     ///< Set block capacity maximum coefficient.
/**/TBlockMultiHostMin/**/,         ///< Set block multihost minimum hosts count.
/**/TBlockMultiHostMax/**/,         ///< Set block multihost maximum hosts count.
/**/TBlockMultiHostWaitMax/**/,     ///< Set block multihost maximum hosts wait time.
/**/TBlockMultiHostWaitSrv/**/,     ///< Set block multihost service start wait time.
/**/TBlockNeedMemory/**/,           ///< Set block render memory need.
/**/TBlockNeedPower/**/,            ///< Set block render power need.
/**/TBlockNeedHDD/**/,              ///< Set block render hdd need.
/**/TBlockNeedProperties/**/,       ///< Set block render properties need.
/**/TBlocksProgress/**/,            ///< Blocks running progress data.
/**/TBlocksProperties/**/,          ///< Blocks progress and properties data.
/**/TBlocks/**/,                    ///< Blocks data.

/**/TTask/**/,                      ///< A task of some job.
/**/TTasksSkip/**/,                 ///< Skip some tasks.
/**/TTasksRestart/**/,              ///< Restart some tasks.
/**/TTaskRequest/**/,               ///< Get task information.
/**/TTaskLogRequest/**/,            ///< Get task information log.
/**/TTaskErrorHostsRequest/**/,     ///< Get task error hosts list.
/**/TTaskOutputRequest/**/,         ///< Job task output request.
/**/TTaskUpdatePercent/**/,         ///< New progress percentage for task.
/**/TTaskUpdateState/**/,           ///< New state for task.
/**/TTaskListenOutput/**/,          ///< Request to send task output to provided address.
/**/TTaskOutput/**/,                ///< Job task output data.
/**/TTasksRun/**/,                  ///< Job tasks run data.

/**/TLAST/**/                       ///< The last type number.
};

static const char * TNAMES[]; ///< Type names.

   inline int   type()  const { return mtype;  }///< Get message type.
   inline char* data()  const { return mdata;  }///< Get data pointer.
   inline int   int32() const { return mint32; }///< Get 32-bit integer, data lenght for data messages.

   inline char* buffer() const { return mbuffer;}///< Get buffer pointer.

/// Get message full size (with data).
   inline int writeSize() const { return mtype<TDATA ? Msg::SizeHeader : Msg::SizeHeader+mint32;}

/// Get buffer at already written postition to write \c size bytes in it.
   char * writtenBuffer( int size);
   inline bool isWriting() const { return  writing; } ///< Writing or reading data in message.
   inline bool isReading() const { return !writing; } ///< Writing or reading data in message.

   void setInvalid();             ///< Set message invalidness.
   bool readHeader( int bytes);   ///< Read header from message buffer, \c bytes - number of already written bytes in it's buffer.

   inline bool      isNull() const { return mtype == TNULL;    }///< Whether message is null.
   inline bool   isInvalid() const { return mtype == TInvalid; }///< Whether message is invalid.

   void stdOut( bool full = false) const;
   void stdOutData();

   static const int SizeHeader;     ///< size of message header.
   static const int SizeBuffer;     ///< message reading buffer size.
   static const int SizeBufferLimit;///< message buffer maximum size.
   static const int SizeDataMax;    ///< maximum data size that can handle a message.
   static const int32_t Version;    ///< Current afanasy version.

   inline int version() const { return mversion; } ///< Get message afanasy version.

   inline void resetWrittenSize() { msgwrittensize = 0; }

private:

// header:
   int32_t mversion;                ///< Afanasy network protocol version.
//   int32_t msid;                    ///< Sender id.
   int32_t mtype;                   ///< Message type.
   int32_t mint32;                  ///< Some 32-bit integer, data length for data messages.

// data poiters:
   char *mdata;                     ///< Data pointer.
   char *mbuffer;                   ///< Buffer pointer.

   bool writing;                    ///< Writing or reading data in message.
   int  mbuffer_size;               ///< Buffer size.
   int  mdata_maxsize;              ///< Data maximum size ( = buffer size - header size).
   int  msgwrittensize;             ///< Number of bytes already written in message buffer.

private:

// private methods:
   void construct();                ///< Called from constuctors.
   bool checkZero( bool outerror ); ///< Check Zero type, data length and pointer.
   bool checkValidness();           ///< Check message header validness;

 /// Allocate memory for buffer, copy \c to_copy_len bytes in new buffer if any
   bool allocateBuffer( int size, int to_copy_len = 0);

   void rw_header( bool write ); ///< Read or write message header.
   void readwrite( Msg * msg);
};
}
