Add the following instructions to the /etc/rsyslog.d/50-default.conf

$template autonomous_vehicle_log_format,"%timegenerated% %programname%:%msg%\n"
local0.*		-/var/log/autonomous_vehicle.log;autonomous_vehicle_log_format

