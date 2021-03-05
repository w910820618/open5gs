/*
 * Copyright (C) 2019 by Sukchan Lee <acetcom@gmail.com>
 *
 * This file is part of Open5GS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "nnssf-handler.h"
#include "nas-path.h"
#include "sbi-path.h"

int amf_nnssf_nsselection_handle_get(
        amf_sess_t *sess, ogs_sbi_message_t *recvmsg)
{
    amf_ue_t *amf_ue = NULL;

    ogs_assert(sess);
    amf_ue = sess->amf_ue;
    ogs_assert(amf_ue);
    ogs_assert(recvmsg);

    ogs_assert(!SESSION_CONTEXT_IN_SMF(sess));

    if (recvmsg->res_status != OGS_SBI_HTTP_STATUS_OK) {
        ogs_error("[%s] HTTP response error [%d]",
                amf_ue->supi, recvmsg->res_status);
        nas_5gs_send_gmm_status(
                amf_ue, OGS_5GMM_CAUSE_5GS_SERVICES_NOT_ALLOWED);
        return OGS_ERROR;
    }

    amf_sess_sbi_discover_and_send(OpenAPI_nf_type_SMF,
            sess, AMF_CREATE_SM_CONTEXT_NO_STATE, NULL,
            amf_nsmf_pdusession_build_create_sm_context);

    return OGS_OK;
}
