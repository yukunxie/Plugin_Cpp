--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

require "UnLua"

local Sphere_Blueprint_C = Class()

--function Sphere_Blueprint_C:Initialize(Initializer)
--end

--function Sphere_Blueprint_C:UserConstructionScript()
--end

function Sphere_Blueprint_C:ReceiveBeginPlay()
    print ("xxxxxxxxxxxxxxxxxx Sphere_Blueprint_C:ReceiveBeginPlay")
end

function Sphere_Blueprint_C:ReceiveEndPlay()
end

function Sphere_Blueprint_C:ReceiveTick(DeltaSeconds)
    print ("xxxxxxxxxxxxxxxxxx Sphere_Blueprint_C:ReceiveTick")
end

--function Sphere_Blueprint_C:ReceiveAnyDamage(Damage, DamageType, InstigatedBy, DamageCauser)
--end

--function Sphere_Blueprint_C:ReceiveActorBeginOverlap(OtherActor)
--end

--function Sphere_Blueprint_C:ReceiveActorEndOverlap(OtherActor)
--end

return Sphere_Blueprint_C
