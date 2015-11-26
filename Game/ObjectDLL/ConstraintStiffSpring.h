//-----------------------------------------------------------------------------
// ConstraintStiffSpring.h
//
// Provides the definition for the stiff spring constraint that connects two
// rigid bodies together at different points that must be a fixed distance
// apart. Most of this functionality comes from the base constraint object, 
// and all this needs to handle is loading in properties and setting up the 
// actual constraint.
//
//-----------------------------------------------------------------------------

#ifndef __CONSTRAINTSTIFFSPRING_H__
#define __CONSTRAINTSTIFFSPRING_H__

#ifndef __CONSTRAINTBASE_H__
#	include "ConstraintBase.h"
#endif

LINKTO_MODULE( ConstraintStiffSpring );

class ConstraintStiffSpring :
	public ConstraintBase
{
public:

	ConstraintStiffSpring();

	//virtual function that derived classes must override to handle loading in of
	//property data. Derived classes should call this for the parent first.
	virtual void		ReadConstraintProperties(const GenericPropList *pProps);

	//this function is called only once when the object is created (NOT when it is loaded), and provides
	//the rigid bodies that the constraint will be linked between. This allows for rigid bodies to handle
	//setting up any data that must be specified in the space of the rigid body. This data should then
	//be saved and loaded and used. This is guaranteed to be called before CreateConstraint, and after
	//all other objects have been created. This should return false if it cannot setup the data
	//and therefore should not create the constraint.
	virtual bool		SetupBodySpaceData(const LTRigidTransform& tInvBody1, const LTRigidTransform& tInvBody2);

	//called to handle actual construction of this constraint
	HPHYSICSCONSTRAINT	CreateConstraint(HPHYSICSRIGIDBODY hBody1, HPHYSICSRIGIDBODY hBody2);

	//handles saving and loading all data to a message stream. Derived classes should
	//call this first in order to work properly
	virtual void	Save(ILTMessage_Write *pMsg, uint32 dwSaveFlags);
	virtual void	Load(ILTMessage_Read *pMsg, uint32 dwLoadFlags);

	// Write data specific to a stiffspring constraint into the create struct...
	virtual void	SetupConstraintCreateStruct( PHYSICSCONSTRAINTCREATESTRUCT &rCS );

private:

	//the name of the associated point object that provides the second body position. 
	std::string		m_sEndPointObject;

	//the pivot point in each rigid body space
	LTVector		m_vPivotPt1;
	LTVector		m_vPivotPt2;

	//the distance to preserve between the points
	float			m_fDistance;
};

#endif
