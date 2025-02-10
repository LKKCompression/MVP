import React, { useState, useEffect } from 'react';
import { View, Text, StyleSheet } from 'react-native';
import { BleManager } from 'react-native-ble-plx';

const manager = new BleManager();

const App = () => {
    const [pressure, setPressure] = useState(null);

useEffect(() => {
    manager.startDeviceScan(null, null, (error, device) => {
        if (error) return;
        if (device.name === "LKK Compression Sock") {
            device.connect().then(() => {
                device.discoverAllServicesAndCharacteristics().then(() => {
                    device.monitorCharacteristicForService(
                        "0000180D-0000-1000-8000-00805f9b34fb",
                        "00002A37-0000-1000-8000-00805f9b34fb",
                        (error, characteristic) => {
                            if (characteristic) {
                                setPressure(characteristic.value);
                            }
                        }
                    );
                });
            });
        }
    });

    return () => manager.stopDeviceScan();
}, []);

    return (
        <View style={styles.container}>
        <Text style={styles.title}>LKK Compression Health Dashboard</Text>
        <Text style={styles.data}>Pressure: {pressure} kPa</Text>
        </View>
    );
};

const styles = StyleSheet.create({
    container: { flex: 1, justifyContent: 'center', alignItems: 'center' },
    title: { fontSize: 22, fontWeight: 'bold' },
    data: { fontSize: 18, marginTop: 20 }
});

export default App;
