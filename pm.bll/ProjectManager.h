#pragma once
#include "ProjectStore.h"
#include "TeamStore.h"
#include "UserStore.h"

namespace pm::bll{
	struct ProjectManager {
		ProjectStore pstore;
		TeamStore tstore;
		UserStore ustore;
	};
}
