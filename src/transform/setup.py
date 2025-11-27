from setuptools import setup

package_name = 'transform'

setup(
    name=package_name,
    version='0.0.1',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
         ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name + '/launch', ['launch/transforms.launch.py']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='YourName',
    maintainer_email='you@email.com',
    description='Static TF publishers for Pepper robot cameras',
    license='Apache License 2.0',
    entry_points={
        'console_scripts': [
            'pepper_tf = transform.transform:main'
        ],
    },
)
