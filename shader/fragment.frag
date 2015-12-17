#version 400

uniform float LineWidth;
uniform vec4 LineColor;
uniform vec4 LightPosition;
uniform vec3 LightIntensity;
uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;
uniform float shininess = 0.3;

noperspective in vec3 EdgeDistance;
in vec3 TENormal;
in vec4 TEPosition;

layout( location = 0 ) out vec4 FragColor;

vec4 phongModel(vec3 pos, vec3 norm ) {
    vec3 s = normalize(vec3(LightPosition) - pos);

    vec3 v = normalize(-pos.xyz);
    vec3 r = reflect( -s, norm );
    vec3 ambient = LightIntensity * Ka;

    float sDotN = max( dot(s,norm), 0.0 );

    vec3 diffuse = LightIntensity * Kd * sDotN;

    vec3 spec = vec3(0.0);

    if( sDotN > 0.0 )
        spec = LightIntensity * Ks *
               pow( max( dot(r,v), 0.0 ), shininess );

    return vec4(ambient + diffuse + spec, 1);
}

float edgeMix()
{
    // Find the smallest distance
    float d = min( min( EdgeDistance.x, EdgeDistance.y ), EdgeDistance.z );

    if( d < LineWidth - 1 ) {
        return 1.0;
    } else if( d > LineWidth + 1 ) {
        return 0.0;
    } else {
        float x = d - (LineWidth - 1);
        return exp2(-2.0 * (x*x));
    }
}

void main()
{
    vec3 Position = vec3(TEPosition.x,TEPosition.y,TEPosition.z);
    vec4 lightColor = phongModel(Position, TENormal);
    float mixVal = edgeMix();
    lightColor = pow( lightColor, vec4(1.0/2.2) );
    FragColor = mix( lightColor, LineColor, mixVal );
}
