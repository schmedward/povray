//******************************************************************************
///
/// @file frontend/rendermessagehandler.h
///
/// @todo   What's in here?
///
/// @copyright
/// @parblock
///
/// Persistence of Vision Ray Tracer ('POV-Ray') version 3.7.
/// Copyright 1991-2014 Persistence of Vision Raytracer Pty. Ltd.
///
/// POV-Ray is free software: you can redistribute it and/or modify
/// it under the terms of the GNU Affero General Public License as
/// published by the Free Software Foundation, either version 3 of the
/// License, or (at your option) any later version.
///
/// POV-Ray is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU Affero General Public License for more details.
///
/// You should have received a copy of the GNU Affero General Public License
/// along with this program.  If not, see <http://www.gnu.org/licenses/>.
///
/// ----------------------------------------------------------------------------
///
/// POV-Ray is based on the popular DKB raytracer version 2.12.
/// DKBTrace was originally written by David K. Buck.
/// DKBTrace Ver 2.0-2.12 were written by David K. Buck & Aaron A. Collins.
///
/// @endparblock
///
//******************************************************************************

#ifndef POVRAY_FRONTEND_RENDERMESSAGEHANDLER_H
#define POVRAY_FRONTEND_RENDERMESSAGEHANDLER_H

#include "frontend/configfrontend.h"
#include "frontend/renderfrontend.h"

namespace pov_frontend
{

class RenderMessageHandler
{
    public:
        RenderMessageHandler();
        virtual ~RenderMessageHandler();

        void HandleMessage(const SceneData&, const ViewData&, POVMSType, POVMS_Object&);
    protected:
        virtual void Options(Console *, POVMS_Object&, bool);
        virtual void Statistics(Console *, POVMS_Object&, bool);
        virtual void Progress(Console *, POVMS_Object&, bool);
        virtual void Warning(Console *, POVMS_Object&, bool);
        virtual void Error(Console *, POVMS_Object&, bool);
        virtual void FatalError(Console *, POVMS_Object&, bool);
};

}

#endif // POVRAY_FRONTEND_RENDERMESSAGEHANDLER_H
