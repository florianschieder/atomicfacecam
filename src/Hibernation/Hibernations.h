#pragma once

#include "pch.h"

/*
 * Hibernations
 * ============
 *
 * A hibernation is a class which is responsible for persisting
 * and loading an object. Furthermore, it can hold resources (or
 * references to resources) which are responsible for those processes,
 * e.g. a file handle, a connection handle, ...
 *
 * Whenever you want to store or load an object, you can implement a
 * concrete hibernation and derive either from `SingleObjectHibernation`,
 * `IdentifiableObjectHibernation` or `CollectionHibernation`.
 */


#include "SingleObjectHibernation.h"
#include "IdentifiableObjectHibernation.h"
#include "RegistryValueHibernation.h"