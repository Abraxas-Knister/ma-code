#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <plog/Log.h>
/* plog is a logging functionality that works like this:
 *
 * each main function will have a line saying
 * ` plog::init(plog::debug, "log/HEADER.log"); `
 * 
 * whenever one wants to turn off logging one turns it off by changing that to
 * ` plog::init(plog::none, "log/HEADER.log"); `
 *
 * This works like that:
 * the plog::none or plog::debug actually set a max severity level that a log
 * message can have, lower severity levels being ignored and none severity level
 * leading to the message being printed to the log always.
 *
 * Levels are:
 *  PLOGN << "none";
 *  PLOGF << "fatal";
 *  PLOGE << "error";
 *  PLOGW << "warning";
 *  PLOGI << "info";
 *  PLOGD << "debug";
 *  PLOGV << "verbose";
 */

/* all typedefs go here
 * were eg going to optimise for performace by using small ints 
 * etc. and therefore will have several different types
 */

#endif
