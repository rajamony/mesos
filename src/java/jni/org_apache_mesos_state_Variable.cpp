#include <jni.h>

#include <string>

#include "state/state.hpp"

using namespace mesos::state;

extern "C" {

/*
 * Class:     org_apache_mesos_state_Variable
 * Method:    value
 * Signature: ()[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_apache_mesos_state_Variable_value
  (JNIEnv* env, jobject thiz)
{
  jclass clazz = env->GetObjectClass(thiz);

  jfieldID __variable = env->GetFieldID(clazz, "__variable", "J");

  Variable* variable = (Variable*) env->GetLongField(thiz, __variable);

  const std::string& value = variable->value();

  // byte[] value = ..;
  jbyteArray jvalue = env->NewByteArray(value.size());
  env->SetByteArrayRegion(jvalue, 0, value.size(), (jbyte*) value.data());

  return jvalue;
}


/*
 * Class:     org_apache_mesos_state_Variable
 * Method:    mutate
 * Signature: ([B)Lorg/apache/mesos/state/Variable;
 */
JNIEXPORT jobject JNICALL Java_org_apache_mesos_state_Variable_mutate
  (JNIEnv* env, jobject thiz, jbyteArray jvalue)
{
  jclass clazz = env->GetObjectClass(thiz);

  jfieldID __variable = env->GetFieldID(clazz, "__variable", "J");

  Variable* variable = (Variable*) env->GetLongField(thiz, __variable);

  jbyte* value = env->GetByteArrayElements(jvalue, NULL);
  jsize length = env->GetArrayLength(jvalue);

  // Mutate the variable and save a copy of the result.
  variable =
    new Variable(variable->mutate(std::string((const char*) value, length)));

  env->ReleaseByteArrayElements(jvalue, value, 0);

  // Variable variable = new Variable();
  clazz = env->FindClass("org/apache/mesos/state/Variable");

  jmethodID _init_ = env->GetMethodID(clazz, "<init>", "()V");
  jobject jvariable = env->NewObject(clazz, _init_);

  env->SetLongField(jvariable, __variable, (jlong) variable);

  return jvariable;
}


/*
 * Class:     org_apache_mesos_state_Variable
 * Method:    finalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_apache_mesos_state_Variable_finalize
  (JNIEnv* env, jobject thiz)
{
  jclass clazz = env->GetObjectClass(thiz);

  jfieldID __variable = env->GetFieldID(clazz, "__variable", "J");

  Variable* variable = (Variable*) env->GetLongField(thiz, __variable);

  delete variable;
}

} // extern "C" {
